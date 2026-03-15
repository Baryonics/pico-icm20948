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
            [params[6], params[7], params[8]],
            [params[9], params[10], params[11]],
        ]
    )
    return result.success, b, A


def plot_data(
    data: npt.NDArray[np.float64],
    b: npt.NDArray[np.float64],
    A: npt.NDArray[np.float64],
):
    def set_equal_axes(ax, data: npt.NDArray[np.float64]):
        x = data[:, 0]
        y = data[:, 1]
        z = data[:, 2]

        xmid = (x.min() + x.max()) / 2.0
        ymid = (y.min() + y.max()) / 2.0
        zmid = (z.min() + z.max()) / 2.0

        radius = (
            max(
                x.max() - x.min(),
                y.max() - y.min(),
                z.max() - z.min(),
            )
            / 2.0
        )

        ax.set_xlim(xmid - radius, xmid + radius)
        ax.set_ylim(ymid - radius, ymid + radius)
        ax.set_zlim(zmid - radius, zmid + radius)

    corrected = (data - b) @ A.T

    fig1 = plt.figure("Raw magnetometer data")
    ax1 = fig1.add_subplot(111, projection="3d")

    ax1.scatter(
        data[:, 0],
        data[:, 1],
        data[:, 2],  # type: ignore[attr-defined]
        s=5,
        label="raw data",
        alpha=0.6,
    )

    ax1.set_xlabel("mag_x")
    ax1.set_ylabel("mag_y")
    ax1.set_zlabel("mag_z")
    ax1.legend()
    ax1.set_title("Raw magnetometer data")
    set_equal_axes(ax1, data)
    ax1.set_box_aspect([1, 1, 1])

    fig2 = plt.figure("Corrected magnetometer data")
    ax2 = fig2.add_subplot(111, projection="3d")

    ax2.scatter(
        corrected[:, 0],
        corrected[:, 1],
        corrected[:, 2],  # type: ignore[attr-defined]
        s=5,
        label="corrected data",
        alpha=0.6,
    )

    ax2.set_xlabel("mag_x")
    ax2.set_ylabel("mag_y")
    ax2.set_zlabel("mag_z")
    ax2.legend()
    ax2.set_title("Corrected magnetometer data")
    set_equal_axes(ax2, corrected)
    ax2.set_box_aspect([1, 1, 1])
    plt.show()


def print_cpp_mat3(A: np.ndarray):
    print("constexpr Mat3<float> MAG_CAL_A = {")
    for col in range(3):
        print(
            f"    Vec3<float>{{ {A[0, col]:.8e}f, {A[1, col]:.8e}f, {A[2, col]:.8e}f }},"
        )
    print("};")


def print_cpp_vec3(b: np.ndarray):
    print(
        f"constexpr Vec3<float> MAG_CAL_B = "
        f"Vec3<float>{{ {b[0]:.8f}f, {b[1]:.8f}f, {b[2]:.8f}f }};"
    )


def main():
    args = parse_args()
    df = pd.read_csv(args.input)
    data = df.values
    center0 = data.mean(axis=0)
    x0 = np.array(
        [
            center0[0],
            center0[1],
            center0[2],
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

    corrected_data = (data - b) @ A.T
    corrected_data = (data - b) @ A.T
    r = np.linalg.norm(corrected_data, axis=1)

    print("b =", b)
    print("A =\n", A)
    print("rank(A) =", np.linalg.matrix_rank(A))
    print("det(A) =", np.linalg.det(A))
    print("radius mean =", r.mean())
    print("radius std =", r.std())
    print("radius min =", r.min())
    print("radius max =", r.max())
    if is_succesfull:
        print("\nCool data, here are your parameters!")
    else:
        print("\nYour data is bad. Do one more dance")

    print("\nCopy these to your firmware:\n")
    print_cpp_mat3(A)
    print_cpp_vec3(b)
    plot_data(data, b, A)


if __name__ == "__main__":
    main()
