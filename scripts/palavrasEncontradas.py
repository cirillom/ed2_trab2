entrada = []
consulta = []
encontrados = 0

with open ("res/strings_entrada.txt","r") as f:
    entrada = f.readlines()

with open ("res/strings_busca.txt","r") as f:
    consulta = f.readlines()

for palavra in consulta:
    if palavra in entrada:
        encontrados += 1

print(encontrados)

