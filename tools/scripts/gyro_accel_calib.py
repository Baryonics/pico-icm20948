import common.serial_data as s_data
import numpy.typing as npt
import numpy as np
import argparse
import serial


def parse_args():
    parser = argparse.ArgumentParser(
        description="""
    Calculate gyroscope and accelerometer calibration parameters.
    """
    )

    parser.add_argument(
        "-p",
        "--port",
        help="Serial port (e.g. /dev/ttyACM0)",
        default="/dev/ttyACM0",
    )

    parser.add_argument(
        "-s",
        "--sample-size",
        help="How many samples are used for calibration.",
        default=100,
    )

    return parser.parse_args()


def calc_accel_scale(
    x_pos_acc_val: npt.NDArray[np.float64],
    x_neg_acc_val: npt.NDArray[np.float64],
    y_pos_acc_val: npt.NDArray[np.float64],
    y_neg_acc_val: npt.NDArray[np.float64],
    z_pos_acc_val: npt.NDArray[np.float64],
    z_neg_acc_val: npt.NDArray[np.float64],
) -> npt.NDArray[np.float64]:
    return np.array(
        [
            (x_pos_acc_val[0] - x_neg_acc_val[0]) / (2 * 9.81),
            (y_pos_acc_val[1] - y_neg_acc_val[1]) / (2 * 9.81),
            (z_pos_acc_val[2] - z_neg_acc_val[2]) / (2 * 9.81),
        ]
    )


def calc_accel_bias(
    x_pos_acc_val: npt.NDArray[np.float64],
    x_neg_acc_val: npt.NDArray[np.float64],
    y_pos_acc_val: npt.NDArray[np.float64],
    y_neg_acc_val: npt.NDArray[np.float64],
    z_pos_acc_val: npt.NDArray[np.float64],
    z_neg_acc_val: npt.NDArray[np.float64],
) -> npt.NDArray[np.float64]:
    return np.array(
        [
            (x_pos_acc_val[0] + x_neg_acc_val[0]) / 2,
            (y_pos_acc_val[1] + y_neg_acc_val[1]) / 2,
            (z_pos_acc_val[2] + z_neg_acc_val[2]) / 2,
        ]
    )


def calc_mean_acc_from_sample(samples: list[s_data.Sample]) -> npt.NDArray[np.float64]:
    return np.array([i.acc for i in samples]).mean(axis=0)


def calc_mean_gyro_from_sample(samples: list[s_data.Sample]) -> npt.NDArray[np.float64]:
    return np.array([i.gyro for i in samples]).mean(axis=0)


def main():
    args = parse_args()

    port = args.port
    sample_size = args.sample_size

    ser = serial.Serial(port, 115200, timeout=1)

    def read_data(dest: list[s_data.Sample], s_size: int):
        for _ in range(s_size):
            try:
                line = ser.readline()
                dest.append(s_data.parse_sample(line))
            except Exception as e:
                print("parse/update error:", repr(e))

    pos_x_data: list[s_data.Sample] = []
    pos_y_data: list[s_data.Sample] = []
    pos_z_data: list[s_data.Sample] = []
    neg_x_data: list[s_data.Sample] = []
    neg_y_data: list[s_data.Sample] = []
    neg_z_data: list[s_data.Sample] = []

    print("________________________________________________________________________")
    print("\nPlace the device flat with the Z-axis pointing up and keep it still.\n")
    input("Press Enter when ready.")
    print("collecting data...")
    read_data(pos_z_data, sample_size)

    print("________________________________________________________________________")
    print("\nPlace the device flat with the Z-axis pointing down and keep it still.\n")
    input("Press Enter when ready.")
    print("collecting data...")
    read_data(neg_z_data, sample_size)

    print("________________________________________________________________________")
    print("\nPlace the device flat with the X-axis pointing up and keep it still.\n")
    input("Press Enter when ready.")
    print("collecting data...")
    read_data(pos_x_data, sample_size)

    print("________________________________________________________________________")
    print("\nPlace the device flat with the X-axis pointing down and keep it still.\n")
    input("Press Enter when ready.")
    print("collecting data...")
    read_data(neg_x_data, sample_size)

    print("________________________________________________________________________")
    print("\nPlace the device flat with the Y-axis pointing up and keep it still.\n")
    input("Press Enter when ready.")
    print("collecting data...")
    read_data(pos_y_data, sample_size)

    print("________________________________________________________________________")
    print("\nPlace the device flat with the Y-axis pointing down and keep it still.\n")
    input("Press Enter when ready.")
    print("collecting data...")
    read_data(neg_y_data, sample_size)

    mean_pos_acc_x = calc_mean_acc_from_sample(pos_x_data)
    mean_pos_acc_y = calc_mean_acc_from_sample(pos_y_data)
    mean_pos_acc_z = calc_mean_acc_from_sample(pos_z_data)
    mean_pos_gyro_x = calc_mean_gyro_from_sample(pos_x_data)
    mean_pos_gyro_y = calc_mean_gyro_from_sample(pos_y_data)
    mean_pos_gyro_z = calc_mean_gyro_from_sample(pos_z_data)

    mean_neg_acc_x = calc_mean_acc_from_sample(neg_x_data)
    mean_neg_acc_y = calc_mean_acc_from_sample(neg_y_data)
    mean_neg_acc_z = calc_mean_acc_from_sample(neg_z_data)
    mean_neg_gyro_x = calc_mean_gyro_from_sample(neg_x_data)
    mean_neg_gyro_y = calc_mean_gyro_from_sample(neg_y_data)
    mean_neg_gyro_z = calc_mean_gyro_from_sample(neg_z_data)

    acc_scale = calc_accel_scale(
        mean_pos_acc_x,
        mean_neg_acc_x,
        mean_pos_acc_y,
        mean_neg_acc_y,
        mean_pos_acc_z,
        mean_neg_acc_z,
    )

    acc_bias = calc_accel_bias(
        mean_pos_acc_x,
        mean_neg_acc_x,
        mean_pos_acc_y,
        mean_neg_acc_y,
        mean_pos_acc_z,
        mean_neg_acc_z,
    )

    print("bias: ", acc_bias)
    print("scale: ", acc_scale)


if __name__ == "__main__":
    main()
