#!/usr/bin/env python3

from types import FunctionType
import pandas as pd
import numpy as np
import argparse
from scipy.optimize import least_squares
import numpy.typing as npt
import matplotlib.pyplot as plt


def parse_args():
    parser = argparse.ArgumentParser(
        description="""
    Calculate calibration parameters from CSV
    """
    )
    parser.add_argument("-i", "--input", help="Input CSV file", default="mag_data.csv")
    return parser.parse_args()


def residuals(
    params: npt.NDArray[np.float64],
    samples: npt.NDArray[np.float64],
) -> npt.NDArray[np.float64]:
    b = params[0:3]

    A = np.array(
        [
            [params[3], params[4], params[5]],
            [params[6], params[7], params[8]],
            [params[9], params[10], params[11]],
        ]
    )

    y = (samples - b) @ A.T
    return np.sum(y * y, axis=1) - 1.0


def fit_params(
    x_0: npt.NDArray[np.float64], res: FunctionType, df: pd.DataFrame
) -> tuple[bool, npt.NDArray[np.float64], npt.NDArray[np.float64]]:
    result = least_squares(res, x_0, args=(df.values,))
    params = result.x

    b = np.array([params[0], params[1], params[2]])
    A = np.array(
        [
            [params[3], params[4], params[5]],
            [params[4], params[6], params[7]],
            [params[5], params[7], params[8]],
        ]
    )
    return result.success, b, A


def plot_data(
    data: npt.NDArray[np.float64],
):
    def set_equal_axes(ax):
        limits = np.array(
            [
                ax.get_xlim(),
                ax.get_ylim(),
                ax.get_zlim(),
            ]
        )
        center = limits.mean(axis=1)
        radius = (limits[:, 1] - limits[:, 0]).max() / 2

        ax.set_xlim(center[0] - radius, center[0] + radius)
        ax.set_ylim(center[1] - radius, center[1] + radius)
        ax.set_zlim(center[2] - radius, center[2] + radius)

    fig = plt.figure()
    ax = fig.add_subplot(111, projection="3d")

    ax.scatter(
        data[:, 0],
        data[:, 1],
        data[:, 2],
        s=5,
        label="raw data",
        alpha=0.6,
    )

    ax.set_xlabel("mag_x")
    ax.set_ylabel("mag_y")
    ax.set_zlabel("mag_z")

    ax.legend()
    ax.set_title("Magnetometer calibration")
    set_equal_axes(ax)

    plt.show()


def main():
    args = parse_args()
    df = pd.read_csv(args.input)
    data = df.values
    x0 = np.array(
        [
            0,
            0,
            0,
            1,
            0,
            0,
            0,
            1,
            0,
            0,
            0,
            1,
        ],
        dtype=float,
    )

    is_succesfull, b, A = fit_params(x0, residuals, df)

    if is_succesfull:
        print("Cool data, here are your parameters!")
    else:
        print("Your data is bad. Do one more dance")

    print(b, A)
    plot_data(data)


if __name__ == "__main__":
    main()
