import matplotlib.pyplot as plt
import numpy

data = numpy.genfromtxt("../data/binary_search/bsearch_begin_comps100.csv", delimiter = ";", names = ["n", "comps"])

plt.scatter(data["n"], data["comps"], color = 'r', label = 'liczba porownan')
#plt.scatter(n,n)
#plt.plot(X,y,color = 'b', label = 'Ograniczenie funkcją sześcienną')
plt.xlabel("Rozmiar instancji")
plt.ylabel("Liczba porównań")
plt.legend()
plt.title("Złożoność obliczeniowa rozszerzonej metody najbliższego sąsiada")
#print(y)
plt.savefig("../plots/extended_neighbour_complexity.png")