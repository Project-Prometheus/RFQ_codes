#include <iostream>
#include <fstream>
#include <math.h>
#include <gsl/gsl_sf_bessel.h>

using namespace std;
int main () {

int opt;
cout << "Welcome to Tou2Lid2Tou_v01" << endl << "Select a feature" << endl << "1) Toutatis2Lidos    2) Lidos2Toutatis" << endl << "Option: ";
cin >> opt;

// Parameters for Lidos input
int LParticleCharge=1;
double LParticleMass=2;
double LBeamCurrent=130.00000; // mA
double LEmittance=0.2500000; // π*cm*mrad
int LMatchingSectionCellNo=7;

// Constants
double lightSpeed=299792458; // m/s

// Variables
double ParticleMass=1875.612859; // MeV
double RFfreq=175.0; // MHz
double Wavelength=lightSpeed/RFfreq/1E4; // cm
int ncell=608;
int pcell=453;

// Toutatis to Lidos
if (opt==1){

ifstream ToutatisIn;
char ToutatisInputFilename[] = "ifmif.inp";
ToutatisIn.open(ToutatisInputFilename, ios::in);

int n[ncell],i;
double a[ncell],m[ncell],w[ncell],beta[ncell],u[ncell],A[ncell],f[ncell],cl[ncell],l[ncell],null[ncell],k[ncell],X[ncell],B[ncell],q[ncell],r[ncell];

for (i=0; i<ncell; i++)
{
	ToutatisIn >> n[i] >> u[i] >> w[i] >> beta[i] >> null[i] >> A[i] >> f[i] >> a[i] >> m[i] >> null[i] >> r[i] >> null[i] >> cl[i] >> l[i] >> null[i] >> null[i];

//k[i]=2*M_PI/(Wavelength*beta[i]);
//X[i]=(gsl_sf_bessel_I0(k[i]*a[i]) + gsl_sf_bessel_I0(k[i]*a[i]*m[i]))/(m[i]*m[i]*gsl_sf_bessel_I0(k[i]*a[i]) + gsl_sf_bessel_I0(k[i]*a[i]*m[i]));
//B[i]=(1/ParticleMass)*(u[i]/a[i])*(1/(RFfreq*RFfreq))*(1/a[i])*X[i];
//q[i]=((u[i]/2000*ParticleMass)*((Wavelength*Wavelength)/(M_PI*M_PI*r[i]*r[i])))*X[i]*((r[i]*r[i])/a[i]*a[i]);
}

ofstream LidosIn;
LidosIn.open("lidos.in"); 
//LidosIn.precision(10);

LidosIn << LParticleCharge << "\t" << LParticleMass << "\t" << Wavelength << "\t" << LBeamCurrent << "\t" << LEmittance << endl;
LidosIn << ncell << "\t" << LMatchingSectionCellNo << endl;

for (i=0; i<ncell; i++)
{
	LidosIn << n[i] << "\t" << l[i] << "\t" << a[i] << "\t" << m[i] << "\t" <<  w[i] << "\t" << beta[i] << "\t" << u[i] << "\t" << A[i] << "\t" << f[i] << "\t" << "B" << "\t" << cl[i] <<endl;
}
LidosIn.close();
cout << "lidos.in is created." << endl;
}


// Lidos to Toutatis
else if (opt==2){

ifstream LIn;
char LidosInputFilename[] = "test_p.par";
LIn.open(LidosInputFilename, ios::in);

int n[pcell],i;
double a[pcell],m[pcell],w[pcell],beta[pcell],u[pcell],A[pcell],f[pcell],cl[pcell],l[pcell],Bp[pcell],R[pcell];

for (i=0; i<pcell; i++)
{
	LIn>>n[i]>>l[i]>>a[i]>>m[i]>>w[i]>>beta[i]>>u[i]>>A[i]>>f[i]>>Bp[i]>>cl[i];

R[i]=0.5*(m[i]+1)*a[i];
}

ofstream TIn;
TIn.open("toutatis.in");

for (i=0; i<pcell; i++)
{
	TIn << n[i] << "\t"<< u[i] << "\t"<< w[i] << "\t"<< beta[i]<< "\t" << 0 << "\t"<<A[i] << "\t"<< f[i]<< "\t" << a[i]<< "\t" << m[i]<< "\t" << R[i] << "\t"<< 0.43608975 << "\t" << 0 << "\t" << cl[i]<< "\t" << l[i]<< "\t" << 0 << "\t"<< 0 << endl;
}
TIn.close();
cout << "toutatis.in is created." << endl;
}

else
{
cout << "Undefined choice, goodbye" << endl;
}
 return 0;
}
