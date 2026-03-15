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
