import matplotlib.pyplot as plt


path = "./measurements/CO2"
fileName = "medicion_CO2_0.txt"

content = []
with open(path + fileName, "r") as file:
    for line in file:
        line = int(line.rstrip("\n"))
        content.append(line)

x = [*range(len(content))]
plt.plot(x, content, "o")
plt.savefig(path + "mediciones_CO2.png")
