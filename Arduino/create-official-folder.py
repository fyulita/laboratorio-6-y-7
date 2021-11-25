import os
import shutil


# PATH
path = "./measurements/full-x4/"

# Carpetas con mediciones "oficiales"
# Es importante que esten en orden
folders_list = ["2021-11-03_17-49-11/", "2021-11-05_16-07-41/", "2021-11-05_18-09-50/", "2021-11-08_14-59-55/", "2021-11-08_15-57-42/", "2021-11-08_18-00-42/"]

# Creamos una carpeta para todas las mediciones "oficiales" llamada `official-run/`
if not os.path.isdir(f"{path}/official-run"):
    os.makedirs(f"{path}/official-run")

# Esta variable va a contar cuantos archivos de datos ya tenemos en la carpeta como para que los nuevos archivos continuen la numeracion
# Si en la primera carpeta hay n archivos entonces el `data_0.csv` de la segunda carpeta ahora es el archivo n+1 y entonces debe llamarse `data_n+1.csv`
rename_counter = 0

for folder in folders_list:
    folder_path = path + folder

    # Esta variable va a contar cuantos archivos csv hay en cada carpeta para al final sumarle al `rename_counter`
    n = 0
    for file in os.listdir(folder_path):
        if file.endswith(".csv"):
            file_number = int(file[5:-4])
            new_file_number = file_number + rename_counter
            new_filename = f"data_{new_file_number}.csv"
            shutil.copyfile(folder_path + file, path + "official-run/" + new_filename)
            n += 1

    rename_counter += n
