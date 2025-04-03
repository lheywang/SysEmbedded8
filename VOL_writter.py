steps = 255
interval = 1 / steps
scaling = 255

for n in range(steps + 1):
    print(
        f"            WHEN {n} => volmod <= {n * interval * scaling:.5} -- Scaling for {n * 100 / 255:.3} % du volume max"
    )
