//---------------------------------ARRAYS.H-----------------------------------
// Headerfile waarin de structures / classes worden gedeclareerd
//----------------------------------------------------------------------------

typedef struct
{ 	int Unieknr;
	char Omschrijving[20];
	float WB;
	float Asafst[4];
	float Hz_onb;
	float Hz_bel;
	float Hschotel;
	float Ballast_VA;
	float Ballast_AA;
	float Onb_asl[6];
	float Onb_asl_mb[6];		// Onbeladen aslast met ballast!
	float Bel_asl[6];
	float Dyn_aslverd[6];
	float Massatr[6];
	float Rdyn[6];
	float Frem[6];
}Voertuig;

typedef struct
{  int Xloc, Yloc, veld1, veld2;
	char voortekst[31];
	char variabele[21];
}inleesrec;

typedef struct
{	int nummer;
	char dyn_stat;
	char mech_pneum;
	char omschr[35];
	char bestelnr[25];
	float Pkar;
	float Stuurkar [10][2];
	float In_uit [10][2];
}ALR_vent;

typedef struct
{	int nummer;
	char omschr[35];
	char bestelnr[25];
	float waarden[10][2];
}XY_vent;

typedef struct
{	int nummer;
	char omschr[35];
	char bestelnr[25];
	float waarden[10][2];
}Veerkar;

typedef struct
{	int nummer;
	char omschr[35];
	char bestelnr[25];
	float Paanspr;		// Aanspreekdruk
	float Pnood;		// Noodstuur druk waarvoor geldt: Als P4 <= Pnood: P2=P1
	float P1_fact;		// Factor waarmee P1 vermenigvuldigd wordt
	float P4_fact;		// Factor waarmee P4 vermenigvuldigd wordt
	float Pinspr;		// Eerste deel van regelkar. waarvoor altijd geldt Puit = Pin
}LL_vent;

typedef struct
{	int Rems_nr;
	int P4_naar;
	int P4_van;
	char type; 				// x:XY_vent a:ALR_vent  l:LL_vent
	float Pin;
	float Puit;
	float P4;				// Deze waarde wordt ingevuld als de kring
							// zonder LL berekend is. De P1 is automatisch
							// de Puit van het vorige record.
	float nummer;			//	Zelfde nummer als "nummer" van XY_vent, ALR_vent etc.
							// nodig voor het zetten van de pointers naar de ventielen.
	XY_vent *XY_pntr;
	ALR_vent *ALR_pntr;
	LL_vent *LL_pntr;
}Rems_vent;

typedef struct
{  char Stuur_asl_code[20];	// tekst in de vorm: v1, v2 a1, a2
	char Stuur_aslasten[20];	// tekst in de vorm: 0 1 2 5 6
	float Onb_aslast;
	float Puit_onb;				// In geval van var. insprong ALR is dit de Pi onbel!
	float Stuur_onb;				// Stuurgrootheid onbel. (ALR hoek of Pbalg)
	float Bel_aslast;
	float Puit_bel;				// In geval van var. insprong ALR is dit de Pi bel!
	float Stuur_bel;				// Stuurgrootheid bel. (ALR hoek of Pbalg)
	float Lstang;					// Alleen in geval van mech ALR
	float Asl_Puitmax;			// Aslast bij de maximale uitgestuurde druk uit ALR
	float Asl_Puitmin;			// Aslast bij de minimale uitgestuurde druk uit ALR
	float Inv_onb;					// Invering bij Onb_aslast
	float Inv_bel;					// Invering bij Bel_aslast
	float Dyn_reg;					// Dynamisch regelpercentage ALR
	int veerkarnr;					// i.v.m. zetten van pointer naar veerkar
	Veerkar *Veerkarak;
}ALR_inst;


// Structure die voor elke berekeningsslag en voor elke kring gevuld wordt
// met waarden tijdens de berekening.
typedef struct
{
	float Pin;				// Per berekeningsslag de ingestuurde druk
	int Nummer;				// Volgnummer van de berekeningen nul na laatste!
	float Z;					// De vertraging van het voertuig
	float Aslasten[6];	// Dynamische aslasten
	float Remkrachten[6];// Dynamische remkrachten
	float Mu[6];			// Berekende Mu waarden
	float Drukken[7];		// Drukken 1 t/m 6 voor aslasten 7e voor Pl-Z grafiek
}Result;

typedef struct
{	int AantalLijnen;				//Aantal begrenzingslijnen maximaal 8
	float BegrLijnen[8][4];		//Array voor de coordinaten van de lijnen
	float maxX;						//Maximale x-waarde op de x_as
	float maxY;						//Maximale y-waarde op de y_as
	int AantX;						//Aantal rasterlijnen op de x_as
	int AantY;						//Aantal rasterlijnen op de y_as
}Grens;

typedef struct
{  char Bakw_Trek;				// Karakter die aangeeft Bakw of Trekker
	float Pstart;           	// Startdruk berekening
	float Peind;					// Einddruk berekening
	float Pstap;					// Stapgrootte
	float Pvoorr;					// Voorraadruk van het systeem
	float ThWB_onb;
	float ThWB_bel;
	float ThWB_Dyn;				// WB voor bepaling duikeffect
	float GVW_onb;
	float GVW_bel;
	float Pso;						// Maximale statische schotellast
	float Po;						// ledig gewicht trekker (incl. eventuele ballast)
	float Paanspr[6];				// Aanspreekdruk [bar]
	float Acil[6];					// Cil opp. cm2
	int Pnaar[7];					// Geeft de ventielnrs. die de assen voorzien
										// van druk. 7e is ventiel naar Pl_Z grafiek!
	int Hpgl_vlgnr;				// Houdt het aantal afdrukken bij van Hpgl "files"
	Grens PlZ_Bakw;				// Structure met grenslijnen PlZ
	Grens PlZ_Trek;				// Structure met grenslijnen PlZ
	Grens MuZ;						// Structure met grenslijnen MuZ
}Rekeninfo;

typedef struct
{	Voertuig *Auto;
	Rems_vent *Kring_1, *Kring_2, *Kring_3, *Kring_4;
	XY_vent *XY_vent_Tabel;
	ALR_vent *ALR_vent_Tabel;
	LL_vent *LL_vent_Tabel;
	Veerkar *Veerkar_Tabel;
	ALR_inst *Instelling;
	Result *Uitk_onb;
	Result *Uitk_bel;
	Rekeninfo *Info;
	int *Pnaar;
}Menus;
