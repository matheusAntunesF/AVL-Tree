import random
Maximo = 1000*100
E=[False for i in range(Maximo+1)]
qt = 0
while (qt < Maximo/100):
    x = random.randrange(1,Maximo)
    if (not E[x]):
        print "insere", x
        print "imprime"
        E[x] = True
        qt += 1
