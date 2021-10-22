Implemente varias estructuras y primitivas para ayudarme a hacer el TP. No me voy a poner a explicar las funciones una por una que hacen, sino que solo voy a aclarar lo que crea necesario.

pokemon_t:

El TDA pokemon es un tipo de dato que contiene: nombre, nivel, fuerza, inteligencia, velocidad y defensa

El TDA entrenador es un tipo de dato que contiene: nombre, victorias, y una lista con sus respectivos pokemones

El TDA salon es un tipo de dato que contiene: una lista con sus respectivos entrenadores, un cantidad entrenadores que me sirve para destruir la lista, un hash con los comandos, y un hash con las reglas.

¿Que son esos hash?
El hash comandos, es un hash que tiene como claves la primera parte de los comandos (la que esta en mayuscula) y como elementos punteros respectivos a las funciones que les corresponden. Me parecio
que un hash era lo mas adecuado por su complejidad de busqueda de O(1) y porque no es algo que iba a estar insertando, borrando, y haciendo rehashes todo el tiempo, sino que la definia cuando creaba
el salon y me olvidaba.

EL hash reglas es algo similar, es un hash que tiene como claves el nombre de las reglas y como elementos, strings que describen como se calcula el resultado de las batallas.

¿Por que los pokemones estan almacenados en listas?
Al ser que los pokemones tienen que quedar ordenados de la misma manera en que estan en el archivo de texto, me parecio conveniente usar una lista, ya que el arbol es una estructura ordenada, y no
se me ocurrio como dejarlos ordenados de la misma manera en un hash. Tambien pense en un vector dinamico, pero ya que tenia la lista implementada con todas sus primitivas decidi usar una lista.

¿Por que los entrenadores estan almacenados en listas?
Para almacenar los entrenadores tuve dos ideas. Un arbol o una lista. El arbol me parecio interesante ya que al tener un comparador podian quedar ordenados alfabeticamente los entrenadores.
La lista tambien me parecio una buena idea, ya que al leer un poco mas el contrato, vi que habia una funcion que tenia que devolver una lista, y tambien ya tenia a los pokemones en listas, y me parecio
que iba a llevar a menos errores y confusiones para mi usar una lista, asi no tenia que estar todo el tiempo pensando en tres estructuras diferentes. Por todo esto, si bien la complejidad de busqueda 
de un arbol es menor al de una lista, me decidi por una lista.

Tambien use algunos pedazos de codigo que tenia del tp1, y los archivos de pruebas que los deje almacenados adentro del src en una carpeta aparte.

Use varias cosas que implemente a lo largo de año para ayudarme, listas, hash, y el util.h del primer tp.

Todo lo relacionado a pokemones y entrenadores esta definido en entrenador.h.

Para leer los comandos basicamente primero separe el string y le pase la primera parte a la tabla de hash, para que busque su funcion asociada, y despues llame a la funcion si no era nula y ahi separe
los parametros.

Hice pruebas separadas para entrenadores.c y para salon.c, pero como eran pocas las de entrenador y el makefile me estaba tirando errores.

Si, ya se que el readme es corto pero la verdad con todos los errores que me saltaron ni yo creo que haya llegado a terminar. (piedaddddd)