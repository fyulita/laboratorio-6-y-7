for i in range(186):
    reader = open(f"data_{i}.csv", "r")
    writer = open(f"new/data_{i}.csv", "w")
    lines = reader.readlines()
    for j in range(len(lines)):
        if j == 0:
            writer.write("Date_Time,CO2,Estado_Valvula_CO2_1,Estado_Valvula_Compost_1,Estado_Valvula_CO2_2,Estado_Valvula_Compost_2,Estado_Valvula_CO2_3,Estado_Valvula_Compost_3,Estado_Valvula_CO2_4,Estado_Valvula_Compost_4,Temp_Compost_1,Temp_Compost_2,Temp_Compost_3,Temp_Compost_4,Temp_Suncho,Estado_Suncho\n")
        else:
            writer.write(lines[j])
