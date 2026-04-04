import common.serial_data as s_data
import numpy.typing as npt
import numpy as np
import argparse
import serial


def parse_args():
    parser = argparse.ArgumentParser(
        description="""
    Calculate gyroscope calibration parameters.
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
        default=1000,
    )

    return parser.parse_args()


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

    samples: list[s_data.Sample] = []

    print("________________________________________________________________________")
    print("\nPlace the device flat and keep it still.\n")
    input("Press Enter when ready.")
    print("collecting data...")
    read_data(samples, sample_size)

    print("bias: ", calc_mean_gyro_from_sample(samples))


if __name__ == "__main__":
    main()
