import csv

with open("PWM_values.csv") as csvfile:
    reader = csv.DictReader(csvfile)

    for row in reader:
        print(
            f"        {int(row["Nclk reel"])} WHEN (freqval = {int(row["ï»¿Code"])}) ELSE -- {row["Note"]} : {row["Frequence"]} Hz"
        )
