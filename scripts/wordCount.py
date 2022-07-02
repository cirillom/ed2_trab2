entrada = []
consulta = []
count = 0

with open ("res/strings_entrada.txt","r") as f:
    entrada = f.readlines()

with open ("res/strings_busca.txt","r") as f:
    consulta = f.readlines()

for i in consulta:
    if i in entrada:
        count += 1

print(count)
