#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

void color(int numero)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), numero);
}

void pausa()
{
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

void encabezado()
{
    system("cls");

    color(11);

    cout << "\n";
    cout << "============================================================\n";
    cout << "                    VYT BANKING                             \n";
    cout << "             SIMULADOR FINANCIERO RD                        \n";
    cout << "============================================================\n";

    color(7);
}

void cargar()
{
    color(10);

    cout << "\nProcesando informacion";

    for(int i = 0; i < 30; i++)
    {
        cout << ".";
        Sleep(35);
    }

    cout << "\n";

    color(7);
}

void guardarOperacion(string nombre, string cedula,
                      double capital, double tasa,
                      int tiempo, double interes,
                      double seguro, double impuestoSeguro,
                      double total, double cuota)
{
    ofstream archivo;

    archivo.open("historial_prestamos.txt", ios::app);

    if(archivo.is_open())
    {
        archivo << "============================================\n";
        archivo << "VYT BANKING - OPERACION\n";
        archivo << "Cliente: " << nombre << "\n";
        archivo << "Cedula: " << cedula << "\n";
        archivo << fixed << setprecision(2);

        archivo << "Capital: RD$ " << capital << "\n";
        archivo << "Tasa anual: " << tasa << "%\n";
        archivo << "Tiempo: " << tiempo << " meses\n";
        archivo << "Interes: RD$ " << interes << "\n";
        archivo << "Seguro: RD$ " << seguro << "\n";
        archivo << "ISC seguro: RD$ " << impuestoSeguro << "\n";
        archivo << "Total: RD$ " << total << "\n";
        archivo << "Cuota: RD$ " << cuota << "\n";

        archivo << "============================================\n\n";

        archivo.close();
    }
}

void comprobante(string nombre, string cedula,
                 double capital, double tasa,
                 int tiempo, double interes,
                 double seguro, double impuestoSeguro,
                 double total, double cuota)
{
    ofstream archivo;

    archivo.open("comprobante_cliente.txt");

    if(archivo.is_open())
    {
        archivo << "============================================\n";
        archivo << "              VYT BANKING                  \n";
        archivo << "       COMPROBANTE DE SIMULACION           \n";
        archivo << "============================================\n\n";

        archivo << "CLIENTE\n";
        archivo << "Nombre: " << nombre << "\n";
        archivo << "Cedula: " << cedula << "\n\n";

        archivo << "DETALLE DEL PRESTAMO\n";
        archivo << fixed << setprecision(2);

        archivo << "Capital solicitado: RD$ " << capital << "\n";
        archivo << "Tasa anual: " << tasa << "%\n";
        archivo << "Plazo: " << tiempo << " meses\n";
        archivo << "Interes total: RD$ " << interes << "\n";
        archivo << "Seguro: RD$ " << seguro << "\n";
        archivo << "ISC del seguro: RD$ " << impuestoSeguro << "\n";
        archivo << "Total estimado: RD$ " << total << "\n";
        archivo << "Cuota estimada: RD$ " << cuota << "\n\n";

        archivo << "============================================\n";
        archivo << "Este documento es una simulacion educativa.\n";
        archivo << "No constituye una oferta bancaria.\n";
        archivo << "============================================\n";

        archivo.close();

        color(10);

        cout << "\nComprobante creado correctamente.\n";
        cout << "Archivo: comprobante_cliente.txt\n";

        color(7);
    }
}

void tablaCuotas(double cuota, int tiempo)
{
    double restante;
    restante = cuota * tiempo;

    cout << "\n";
    color(11);

    cout << "====================================================\n";
    cout << "                 TABLA DE CUOTAS                    \n";
    cout << "====================================================\n";

    color(7);

    cout << left;
    cout << setw(10) << "Cuota"
         << setw(20) << "Pago"
         << setw(20) << "Saldo estimado" << endl;

    cout << "----------------------------------------------------\n";

    for(int i = 1; i <= tiempo; i++)
    {
        restante = restante - cuota;

        cout << setw(10) << i
             << "RD$ " << setw(15) << fixed << setprecision(2) << cuota
             << "RD$ " << setw(15) << restante
             << endl;
    }

    cout << "====================================================\n";
}

void nuevaSimulacion()
{
    string nombre;
    string cedula;

    double capital;
    double tasa;
    double seguro;
    double impuestoSeguro;

    int tiempo;
    int opcionSeguro;

    double interes;
    double total;
    double cuota;

    encabezado();

    color(14);

    cout << "\n              NUEVA SIMULACION\n\n";

    color(7);

    cout << "Nombre del cliente: ";
    getline(cin, nombre);

    cout << "Cedula: ";
    getline(cin, cedula);

    cout << "\nMonto del prestamo: RD$ ";
    cin >> capital;

    cout << "Tasa de interes anual (%): ";
    cin >> tasa;

    cout << "Tiempo del prestamo (meses): ";
    cin >> tiempo;

    cout << "\n";
    color(11);

    cout << "SEGURO\n";
    color(7);

    cout << "[1] Sin seguro\n";
    cout << "[2] Seguro basico\n";
    cout << "[3] Seguro personalizado\n";

    cout << "\nSeleccione: ";
    cin >> opcionSeguro;

    seguro = 0;

    if(opcionSeguro == 1)
    {
        seguro = 0;
    }
    else if(opcionSeguro == 2)
    {
        seguro = 500;
    }
    else if(opcionSeguro == 3)
    {
        cout << "Monto del seguro: RD$ ";
        cin >> seguro;
    }
    else
    {
        cout << "\nOpcion incorrecta. Se utilizara sin seguro.\n";
        seguro = 0;
    }

    cargar();

    interes = capital * (tasa / 100) * (tiempo / 12.0);

    impuestoSeguro = seguro * 0.16;

    total = capital + interes + seguro + impuestoSeguro;

    cuota = total / tiempo;

    system("cls");

    color(10);

    cout << "\n";
    cout << "============================================================\n";
    cout << "                  RESULTADO DE SIMULACION                   \n";
    cout << "============================================================\n";

    color(7);

    cout << fixed << setprecision(2);

    cout << "\nCLIENTE\n";
    cout << "Nombre: " << nombre << endl;
    cout << "Cedula: " << cedula << endl;

    cout << "\nDATOS DEL PRESTAMO\n";
    cout << "Capital solicitado : RD$ " << capital << endl;
    cout << "Tasa anual         : " << tasa << "%" << endl;
    cout << "Tiempo             : " << tiempo << " meses" << endl;

    cout << "\nDESGLOSE\n";

    color(14);

    cout << "Interes total      : RD$ " << interes << endl;
    cout << "Seguro             : RD$ " << seguro << endl;
    cout << "ISC seguro         : RD$ " << impuestoSeguro << endl;

    color(10);

    cout << "\nTOTAL A PAGAR      : RD$ " << total << endl;
    cout << "CUOTA ESTIMADA     : RD$ " << cuota << endl;

    color(7);

    cout << "\n";

    tablaCuotas(cuota, tiempo);

    guardarOperacion(nombre, cedula,
                     capital, tasa, tiempo,
                     interes, seguro,
                     impuestoSeguro,
                     total, cuota);

    comprobante(nombre, cedula,
                capital, tasa, tiempo,
                interes, seguro,
                impuestoSeguro,
                total, cuota);

    pausa();
}

void calculadora()
{
    double capital;
    double tasa;
    int tiempo;

    double interes;
    double total;
    double cuota;

    encabezado();

    color(14);

    cout << "\n              CALCULADORA BANCARIA\n\n";

    color(7);

    cout << "Capital: RD$ ";
    cin >> capital;

    cout << "Tasa anual (%): ";
    cin >> tasa;

    cout << "Tiempo en meses: ";
    cin >> tiempo;

    interes = capital * (tasa / 100) * (tiempo / 12.0);

    total = capital + interes;

    cuota = total / tiempo;

    cout << fixed << setprecision(2);

    cout << "\n";
    color(11);

    cout << "RESULTADO\n";

    color(7);

    cout << "\nInteres total: RD$ " << interes << endl;
    cout << "Total: RD$ " << total << endl;
    cout << "Cuota: RD$ " << cuota << endl;

    pausa();
}

void historial()
{
    ifstream archivo;

    string linea;

    encabezado();

    color(14);

    cout << "\n              HISTORIAL DE OPERACIONES\n\n";

    color(7);

    archivo.open("historial_prestamos.txt");

    if(!archivo.is_open())
    {
        cout << "Todavia no existen operaciones guardadas.\n";
        pausa();
        return;
    }

    while(getline(archivo, linea))
    {
        cout << linea << endl;
    }

    archivo.close();

    pausa();
}

void explicacion()
{
    encabezado();

    color(11);

    cout << "\n              COMO SE CALCULA UNA CUOTA\n\n";

    color(7);

    cout << "1. CAPITAL\n";
    cout << "   Es el dinero que el cliente solicita.\n\n";

    cout << "2. TASA DE INTERES\n";
    cout << "   Es el porcentaje anual utilizado para calcular\n";
    cout << "   el interes del prestamo.\n\n";

    cout << "3. TIEMPO\n";
    cout << "   Es la cantidad de meses del prestamo.\n\n";

    cout << "4. INTERES\n";
    cout << "   Formula utilizada en esta simulacion:\n\n";

    color(14);

    cout << "   interes = capital * (tasa / 100) * (tiempo / 12)\n\n";

    color(7);

    cout << "5. TOTAL\n";
    cout << "   capital + interes + costos adicionales.\n\n";

    cout << "6. CUOTA\n";
    cout << "   Es el monto estimado que se paga cada mes.\n\n";

    cout << "7. SEGURO\n";
    cout << "   Puede representar un costo adicional asociado\n";
    cout << "   al financiamiento, dependiendo del producto.\n";

    pausa();
}

void acerca()
{
    encabezado();

    color(11);

    cout << "\n";
    cout << "============================================================\n";
    cout << "                    VYT BANKING                             \n";
    cout << "============================================================\n";

    color(7);

    cout << "\nProyecto: Calculo Bancario\n";
    cout << "Desarrollador: Victor Junior Tejada\n";
    cout << "Lenguaje: C++\n";
    cout << "Version: 1.0\n\n";

    cout << "Objetivo:\n";
    cout << "Ayudar al usuario a comprender de manera clara\n";
    cout << "como se estructura el costo de un prestamo.\n\n";

    cout << "El sistema genera comprobantes y guarda\n";
    cout << "las operaciones realizadas.\n";

    pausa();
}

int main()
{
    int opcion;

    do
    {
        encabezado();

        color(11);

        cout << "\n";
        cout << "                 MENU PRINCIPAL\n\n";

        color(7);

        cout << "[1] Nueva simulacion\n";
        cout << "[2] Calculadora bancaria\n";
        cout << "[3] Historial de operaciones\n";
        cout << "[4] Como se calcula mi cuota?\n";
        cout << "[5] Acerca del sistema\n";
        cout << "[0] Salir\n";

        color(14);

        cout << "\nSeleccione una opcion: ";

        color(7);

        cin >> opcion;
        cin.ignore();

        if(opcion == 1)
        {
            nuevaSimulacion();
        }
        else if(opcion == 2)
        {
            calculadora();
        }
        else if(opcion == 3)
        {
            historial();
        }
        else if(opcion == 4)
        {
            explicacion();
        }
        else if(opcion == 5)
        {
            acerca();
        }
        else if(opcion == 0)
        {
            encabezado();

            color(10);

            cout << "\nGracias por utilizar VYT BANKING.\n";
            cout << "Su informacion financiera merece claridad.\n\n";

            color(7);
        }
        else
        {
            color(12);

            cout << "\nOpcion incorrecta.\n";

            color(7);

            Sleep(1000);
        }

    }while(opcion != 0);

    return 0;
}
