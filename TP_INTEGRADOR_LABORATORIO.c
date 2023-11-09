#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <string.h>

struct BANCO
{
    int numero_cuenta;
    char contrasena[20];
    char nombre[50];
    int saldo;
    char estado[10];
    int intentos;
    int operaciones;
};

int i, j, k, pos;

void CARGA(struct BANCO *clientes);
void DEPOSITO(struct BANCO *nuevo);
void EXTRAER(struct BANCO *extra);
void CONSULTA_SALDO(struct BANCO *consulta);
void OPCION_5(struct BANCO *mirar);
void TRANSFERENCIA(struct BANCO *mover);

int main()
{
    int opcion, cliente_pedido, bole = 0;
    int final;
    char clave[20];

    struct BANCO clientes[10];

    CARGA(clientes);

    int valido = 0;
    do
    {
        do
        {
            printf("\nINGRESE EL NUMERO DE CLIENTE: ");
            scanf("%i", &cliente_pedido);

            printf("INGRESE LA CLAVE: ");
            scanf("%s", &clave);

            for (i = 0; i < 10; i++)
            {
                if (clientes[i].numero_cuenta == cliente_pedido)
                {
                    if (strcmp(clientes[i].contrasena, clave) == 0)
                    {
                        pos = i;
                        bole = 1;
                        valido = 1;
                        i = 9;
                    }
                    else
                    {
                        if (strcmp(clientes[i].contrasena, clave) != 0)
                        {
                            printf("\nClave incorrecta.\n");
                            i = 9;
                        }
                        clientes[i].intentos += 1;
                    }
                }
                else
                {
                    if ((i == 9) && (clientes[i].numero_cuenta != cliente_pedido))
                    {
                        printf("\nNumero de cuenta incorrecto.\n");
                    }
                }

                if (clientes[i].intentos >= 3)
                {
                    i = 9;
                    printf("\nNo se permiten mas intentos.\n");
                    printf("\n");
                    valido = 1;
                }
            }

        } while (valido == 0);

        if (bole == 1)
        {
            do
            {
                printf("\nSeleccione una opcion:\n");
                printf("1. Realizar un Deposito\n");
                printf("2. Realizar una Extraccion\n");
                printf("3. Consultar el Saldo de la Cuenta\n");
                printf("4. Realizar una Transferencia entre Cuentas\n");
                printf("5. Mostrar cantidad de Operaciones Realizadas y Saldo Actual\n");
                printf("6. Salir de la Sesion\n");
                printf("Opcion: ");
                scanf("%d", &opcion);
                while ((opcion < 1) || (opcion > 6))
                {
                    printf("\nOPCION INCORRECTA\nVUELVA A INGRESARLA: ");
                    scanf("%i", &opcion);
                }

                switch (opcion)
                {
                case 1:
                    if (clientes[pos].operaciones != 0)
                    {
                        DEPOSITO(clientes);
                        clientes[pos].operaciones--;
                    }
                    else
                    {
                        printf("\nNO TIENE OPERACIONES DISPONIBLES\n");
                    }

                    break;

                case 2:
                    if (clientes[pos].operaciones != 0)
                    {
                        if (clientes[pos].saldo == 0)
                        {
                            printf("\nSALDO INSUFICIENTE\n");
                        }
                        else
                        {
                            EXTRAER(clientes);
                            clientes[pos].operaciones--;
                        }
                    }
                    else
                    {
                        printf("\nNO TIENE OPERACIONES DISPONIBLES\n");
                    }
                    break;

                case 3:
                    if (clientes[pos].operaciones != 0)
                    {
                        CONSULTA_SALDO(clientes);
                        clientes[pos].operaciones--;
                        break;
                    }
                    else
                    {
                        printf("\nNO TIENE OPERACIONES DISPONIBLES\n");
                    }
                    break;

                case 4:
                    TRANSFERENCIA(clientes);
                    break;

                case 5:
                    OPCION_5(clientes);
                    break;
                }

            } while (opcion != 6);
        }

        printf("\nQUIERE INGRESAR OTRA CUENTA?");
        printf("\n1. SI");
        printf("\n0. NO");
        printf("\nOPCION: ");
        scanf("%i", &final);
        while (final < 0 || final > 1)
        {
            printf("\nVALOR INCORRECTO");
            printf("\n1. SI");
            printf("\n0. NO");
            printf("\nOPCION: ");
            scanf("%i", &final);
        }

        if (final == 1)
        {
            for (i = 0; i < 10; i++)
            {
                clientes[i].operaciones = 10;
                clientes[i].intentos = 0;
                bole = 0;
                valido = 0;
            }
        }

    } while (final == 1);

    return 0;
}

void DEPOSITO(struct BANCO *depo)
{
    int monto;

    printf("\nINGRESE EL MONTO A DEPOSTAR: ");
    scanf("%i", &monto);
    while ((monto < 1) || (monto > 50000))
    {
        printf("\nEL MONTO NO PUEDE SER NEGATIVO O MAYOR A 50.000\nVUELVA A INGRESARLO: ");
        scanf("%i", &monto);
    }

    printf("\nOPERACION REALIZADA\n");
    depo[pos].saldo += monto;
}

void EXTRAER(struct BANCO *extra)
{
    int monto;

    printf("\nINGRESE EL MONTO A EXTRAER: ");
    scanf("%i", &monto);
    while ((monto < 1) || (monto > 50000))
    {
        printf("\nEL MONTO NO PUEDE SER NEGATIVO O MAYOR A 50.000\nVUELVA A INGRESARLO: ");
        scanf("%i", &monto);
    }

    if (extra[pos].saldo > monto)
    {
        printf("\nOPERACION REALIZADA\n");
        extra[pos].saldo -= monto;
    }
    else
    {
        printf("\nSALDO INSUFICIENTE\n");
    }
}

void CONSULTA_SALDO(struct BANCO *consulta)
{
    printf("\nSU SALDO ES DE %i\n", consulta[pos].saldo);
}

void TRANSFERENCIA(struct BANCO *mover)
{
    int numero, cantidad, lugar;
    printf("\nINGRESE EL NUMERO DE CUENTA A LA QUE QUIERE TRASFERIR: ");
    scanf("%i", &numero);
    for (i = 0; i < 10; i++)
    {
        if (mover[i].numero_cuenta == numero)
        {
            lugar = i;
            i = 9;
            printf("INGRESE LA CANTIDAD QUE QUIERE TRANSFERIR: ");
            scanf("%i", &cantidad);
            while (cantidad < 0)
            {
                printf("\nLA CANTIDAD NO PUEDE SER MENOR A 0\n");
                scanf("%i", &cantidad);
            }

            if (cantidad != 0)
            {
                if (mover[pos].saldo > cantidad)
                {
                    mover[pos].saldo -= cantidad;
                    mover[lugar].saldo += cantidad;
                    printf("\n CUENTA 100 = %i", mover[lugar].saldo);
                }
                else
                {
                    printf("\nNO TIENE SALDO SUFICIENTE\n");
                }
            }
            else
            {
                printf("\nOPERACION CANCELADA\n");
            }
        }
        else
        {
            if ((i == 9) && (mover[9].numero_cuenta != numero))
            {
                printf("\nNO SE ENCONTRO EL NUMERO DE CUENTA\n");
            }
        }
    }
}

void OPCION_5(struct BANCO *mirar)
{
    printf("\nOPERACIONES RESTANTES = %i", mirar[pos].operaciones);
    printf("\nSU SALDO ES DE %i\n", mirar[pos].saldo);
}

void CARGA(struct BANCO *clientes)
{
    clientes[0].numero_cuenta = 999;
    strcpy(clientes[0].contrasena, "999");
    strcpy(clientes[0].nombre, "Alan Wake");
    clientes[0].saldo = 100000;
    strcpy(clientes[0].estado, "ACTIVO");
    clientes[0].intentos = 0;
    clientes[0].operaciones = 10;

    clientes[1].numero_cuenta = 100;
    strcpy(clientes[1].contrasena, "usuario100");
    strcpy(clientes[1].nombre, "Gabriel Sarmiento");
    clientes[1].saldo = 0;
    strcpy(clientes[1].estado, "ACTIVO");
    clientes[1].intentos = 0;
    clientes[1].operaciones = 10;

    clientes[2].numero_cuenta = 200;
    strcpy(clientes[2].contrasena, "usuario200");
    strcpy(clientes[2].nombre, "Fernando Malardo");
    clientes[2].saldo = 200;
    strcpy(clientes[2].estado, "ACTIVO");
    clientes[2].intentos = 0;
    clientes[2].operaciones = 10;

    clientes[3].numero_cuenta = 300;
    strcpy(clientes[3].contrasena, "usuario300");
    strcpy(clientes[3].nombre, "Frank Cabra");
    clientes[3].saldo = 300;
    strcpy(clientes[3].estado, "ACTIVO");
    clientes[3].intentos = 0;
    clientes[3].operaciones = 10;

    clientes[4].numero_cuenta = 400;
    strcpy(clientes[4].contrasena, "usuario400");
    strcpy(clientes[4].nombre, "Juan Gutierrez");
    clientes[4].saldo = 60000;
    strcpy(clientes[4].estado, "ACTIVO");
    clientes[4].intentos = 0;
    clientes[4].operaciones = 10;

    clientes[5].numero_cuenta = 500;
    strcpy(clientes[5].contrasena, "usuario500");
    strcpy(clientes[5].nombre, "Cristiano Messi");
    clientes[5].saldo = 45000;
    strcpy(clientes[5].estado, "ACTIVO");
    clientes[5].intentos = 0;
    clientes[5].operaciones = 10;

    clientes[6].numero_cuenta = 600;
    strcpy(clientes[6].contrasena, "usuario600");
    strcpy(clientes[6].nombre, "Gaston");
    clientes[6].saldo = 100000;
    strcpy(clientes[6].estado, "ACTIVO");
    clientes[6].intentos = 0;
    clientes[6].operaciones = 10;

    clientes[7].numero_cuenta = 700;
    strcpy(clientes[7].contrasena, "usuario700");
    strcpy(clientes[7].nombre, "Mateo Descenso");
    clientes[7].saldo = 1234890;
    strcpy(clientes[7].estado, "ACTIVO");
    clientes[7].intentos = 0;
    clientes[7].operaciones = 10;

    clientes[8].numero_cuenta = 800;
    strcpy(clientes[8].contrasena, "usuario800");
    strcpy(clientes[8].nombre, "Juan Gutierrez");
    clientes[8].saldo = 60000;
    strcpy(clientes[8].estado, "ACTIVO");
    clientes[8].intentos = 0;
    clientes[8].operaciones = 10;

    clientes[9].numero_cuenta = 900;
    strcpy(clientes[9].contrasena, "usuario900");
    strcpy(clientes[9].nombre, "Peter Kaka");
    clientes[9].saldo = 95000;
    strcpy(clientes[9].estado, "ACTIVO");
    clientes[9].intentos = 0;
    clientes[9].operaciones = 10;
}
