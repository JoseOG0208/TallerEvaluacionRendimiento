#**************************************************************
#Pontificia Universidad Javeriana
#Nombre: Jose David Ontiveros
#Fecha: 05/05/2025
#Sistemas Operativos
#Taller de Evaluación de Rendimiento
#****************************************************************/

#!/usr/bin/perl

#obtener el directorio de trabajo actual y almacenarlo en $Path
$Path = `pwd`;
chomp($Path);  # Remover el salto de línea del final de $Path

#definir el nombre del ejecutable
$Nombre_Ejecutable = "MM_ejecutable";

#definir los tamaños de la matriz que se usarán en las pruebas
@Size_Matriz = ("200", "300");

#definir los numeros de hilos a usar en las pruebas
@Num_Hilos = (1, 2);

#definir cuantas veces se ejecutará cada combinación de tamaño de matriz y numero de hilos
$Repeticiones = 2;

#bucle para iterar sobre cada tamaño de matriz
foreach $size (@Size_Matriz) {
    #bucle para iterar sobre cada numero de hilos
    foreach $hilo (@Num_Hilos) {
        #definir el nombre del archivo de salida que almacenara los resultados de cada combinacion
        $file = "$Path/$Nombre_Ejecutable-" . $size . "-Hilos-" . $hilo . ".dat";
        
        #bucle para repetir la ejecucion el numero de veces indicado en $Repeticiones
        for ($i = 0; $i < $Repeticiones; $i++) {
            #ejecución del comando y almacenamiento de la salida en el archivo
            #descomentar la siguiente linea despues de prueba mas abajo

            #imprimir el comando que se ejecutaria en lugar de ejecutarlo, eliminar despues de prueba
            printf("$Path/$Nombre_Ejecutable $size $hilo \n");
        }
        #cerrar el archivo
        close($file);
        
        #incrementar el contador $p 
        $p = $p + 1;
    }
}
