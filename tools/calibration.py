import numpy as np
import numpy.typing as npt
from scipy.optimize import least_squares
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import serial


class Sample:
    acc: list[float]
    gyro: list[float]
    mag: list[float]

    def __init__(
        self,
        acc_: list[float],
        gyro_: list[float],
        mag_: list[float],
    ):
        self.acc = acc_
        self.gyro = gyro_
        self.mag = mag_


def parse_sample(input: bytes) -> Sample:
    raw_vals = input.decode("utf-8").strip().split(",")
    acc = [float(raw) for raw in raw_vals[0:3]]
    gyro = [float(raw) for raw in raw_vals[3:6]]
    mag = [float(raw) for raw in raw_vals[6:9]]
    return Sample(acc, gyro, mag)


def calibrate_gyro(samples: list[Sample]) -> npt.NDArray[np.float64]:
    gyro_vals = np.array([sample.gyro for sample in samples])
    return np.mean(gyro_vals, axis=0)


def calibrate_mag(
    samples: list[Sample],
) -> tuple[npt.NDArray[np.float64], npt.NDArray[np.float64]]:
    mag_vals = np.array([sample.mag for sample in samples], dtype=float)

    mag_min = np.min(mag_vals, axis=0)
    mag_max = np.max(mag_vals, axis=0)

    bias0 = (mag_max + mag_min) / 2.0
    radii0 = (mag_max - mag_min) / 2.0
    avg_radius0 = np.mean(radii0)
    scale0 = avg_radius0 / radii0

    x0 = np.concatenate([bias0, scale0])  # [bx, by, bz, sx, sy, sz]

    def residuals(params: npt.NDArray[np.float64]) -> npt.NDArray[np.float64]:
        bias = params[0:3]
        scale = params[3:6]

        corrected = (mag_vals - bias) * scale
        norms = np.linalg.norm(corrected, axis=1)

        target = np.mean(norms)
        return norms - target

    result = least_squares(residuals, x0)

    bias = result.x[0:3]
    scale_factors = result.x[3:6]
    scale_matrix = np.diag(scale_factors)

    return bias, scale_matrix


def __main__():
    pass
    # ser = serial.Serial("/dev/ttyACM0", 115200, timeout=1)
    # sample_buffer = []
    #
    # print("=== ICM20948 calibration tool ===")
    # print("\n")
    #
    # print("## Gyro Calibration ##")
    # print("Lay your device flat on a surface")
    # print("measuring...")
    #
    # i = 1
    # while i <= 100:
    #     line = ser.readline()
    #     if not line:
    #         continue
    #     sample_buffer.append(parse_sample(line))
    #     i += 1
    # print("done")
    # sample_buffer = []
    #
    # gyro_bias = calibrate_gyro(sample_buffer)
    # print("calculated gyro bias: ", gyro_bias)
    #
    # print("## Magnetometer calibration")
    # print("Rotate your device on every axis")
    # print("measuring...")
    #
    # i = 1
    # while i <= 1000:
    #     line = ser.readline()
    #     if not line:
    #         continue
    #     sample_buffer.append(parse_sample(line))
    #     i += 1
    # print("done")
    #
    # print("calculating mag hard and softiron parameters")
    # print(calibrate_mag(sample_buffer))


__main__()
