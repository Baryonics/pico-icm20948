import threading
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import serial
import common.serial_data as s_data
import pandas as pd


def padded_limits(values: list[float]) -> tuple[float, float]:
    vmin = min(values)
    vmax = max(values)

    if vmin == vmax:
        return vmin - 1.0, vmax + 1.0

    pad = (vmax - vmin) * 0.1
    return vmin - pad, vmax + pad


def __main__():
    ser = serial.Serial("/dev/ttyACM0", 115200, timeout=1)

    x_data: list[float] = []
    y_data: list[float] = []
    z_data: list[float] = []

    fig = plt.figure()
    ax = fig.add_subplot(111, projection="3d")

    scatter = ax.scatter([], [], [])  # type: ignore[attr-defined]

    ax.set_xlabel("mag x")
    ax.set_ylabel("mag y")
    ax.set_zlabel("mag z")

    def save_data():
        data = {"mag_x": x_data, "mag_y": y_data, "mag_z": z_data}
        df = pd.DataFrame(data)
        df.to_csv("mag_data.csv", index=False)

    def on_key(event):
        if event.key == " ":
            print("animation stopped")
            ani.event_source.stop()
            save_data()

    fig.canvas.mpl_connect("key_press_event", on_key)

    threading.Thread(target=on_key, daemon=True).start()

    def update(_):
        try:
            line = ser.readline()
            if not line:
                return (scatter,)

            sample = s_data.parse_sample(line)

            mx = float(sample.mag[0])
            my = float(sample.mag[1])
            mz = float(sample.mag[2])

            print(f"mag = {mx}, {my}, {mz}")

            x_data.append(mx)
            y_data.append(my)
            z_data.append(mz)

            scatter._offsets3d = (x_data, y_data, z_data)  # type: ignore[attr-defined]

            xmin, xmax = padded_limits(x_data)
            ymin, ymax = padded_limits(y_data)
            zmin, zmax = padded_limits(z_data)

            ax.set_xlim(xmin, xmax)
            ax.set_ylim(ymin, ymax)
            ax.set_zlim(zmin, zmax)

        except Exception as e:
            print("parse/update error:", repr(e))

        return (scatter,)

    ani = FuncAnimation(fig, update, interval=5, blit=False)
    plt.show()


__main__()
