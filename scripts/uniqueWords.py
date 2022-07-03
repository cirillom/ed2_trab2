words = []
count = 0

with open ("res/strings_entrada.txt","r") as f:
    # Get a list of lines in the file and covert it into a set
    words = set(f.readlines()) 
    count = len(words) 

print(count)