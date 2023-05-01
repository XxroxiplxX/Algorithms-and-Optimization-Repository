from os import system
heuristic = "improved"
for i in range(10):
    k=21
    while (k < 26):
        system("bash launcher.sh " + heuristic + " " + str(k) + " ../stats/" + heuristic + str(k) + ".csv")
        k+=1