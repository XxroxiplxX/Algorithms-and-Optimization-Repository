import matplotlib.pyplot as plt
import numpy
n=[]
for x in range(20):
    n.append(x)
data = numpy.genfromtxt("../stats/improved22.csv", delimiter = ";", names = ["comparisons", "no"])
#data.sort()
for i in range(20):
    data["no"] = i
plt.scatter(data["no"], data["comparisons"], color = 'r', label = 'liczba przeszukanych stanow')
#plt.scatter(n,n)
#plt.plot(X,y,color = 'b', label = 'Ograniczenie funkcją sześcienną')
plt.xlabel("Rozmiar instancji")
plt.ylabel("Liczba porównań")
plt.legend()
plt.title("Złożoność obliczeniowa rozszerzonej metody najbliższego sąsiada")
#print(y)
plt.savefig("../plots/extended_neighbour_complexity.png")