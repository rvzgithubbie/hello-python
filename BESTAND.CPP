#include "prototyp.h"

void Leesdata(Menus *Hoofdmenu);
void Schrijfdata(Menus *Hoofdmenu);
int Schrijfstruct(void *s, size_t size, char * filename, int n);
int Leesstruct(void *s, size_t size, char * filename, int n);

extern Groep Voertuiggroep;
extern char GegevensBestand[80]; // string die de filenaam van de gegevens bevat

//===========================================================================
int Schrijfstruct(void * s, size_t size, char * filename, int n)
{	FILE *stream;
	if ((stream = fopen(filename, "wb")) == NULL)
	{
		fprintf(stderr, "Cannot open output file: \"%s\"\n", filename);
		getch();
		return 1;
	}
	fwrite(s, size, n, stream); /* write struct s to file */
	fclose(stream); /* close file */
	return 0;
}

//===========================================================================
int Leesstruct(void * s, size_t size, char * filename, int n)
{	FILE *stream;
	/*
	int handle;
	if ((handle = open(filename, O_BINARY | S_IREAD)) == -1)
	{
		perror("Error:");
		return 1;
	}
	//display the size of the file
	printf("file length in bytes: %ld\n", filelength(handle));
	printf("Structure sizein bytes: %d\n", size);
	// close the file
	close(handle);
	getch();
	*/


	if ((stream = fopen(filename, "rb")) == NULL)
	{
		fprintf(stderr, "Cannot open input file: \"%s\"\n", filename);
		getch();
		return 1;
	}
	fread(s, size, n, stream); /* read struct s from file */
	fclose(stream); /* close file */
	return 0;
}

//===========================================================================
/*
void Leesdata(Menus * Hoofdmenu)
{
	Leesstruct(Hoofdmenu->Info, sizeof(Rekeninfo), "instel.dat", 1);
	Leesstruct(Hoofdmenu->Auto, sizeof (Voertuig), "auto.dat", 1);
	Leesstruct(Hoofdmenu->Kring_1, sizeof (Rems_vent), "kring1.dat", 10);
	Leesstruct(Hoofdmenu->Kring_2, sizeof (Rems_vent), "kring2.dat",10);
	Leesstruct(Hoofdmenu->Kring_3, sizeof (Rems_vent), "kring3.dat",10);
	Leesstruct(Hoofdmenu->Kring_4, sizeof (Rems_vent), "kring4.dat",10);
	Leesstruct(Hoofdmenu->Instelling, sizeof (ALR_inst), "alrinst.dat", 4);
	Leesstruct(&Voertuiggroep, sizeof (Groep), "voertgrp.dat", 1);

	Init_remschema(Hoofdmenu);

}*/

/*
void Schrijfdata(Menus * Hoofdmenu)
{	Schrijfstruct(Hoofdmenu->Info, sizeof(Rekeninfo), "instel.dat", 1);
	Schrijfstruct(Hoofdmenu->Auto, sizeof (Voertuig), "auto.dat", 1);
	Schrijfstruct(Hoofdmenu->Kring_1, sizeof (Rems_vent), "kring1.dat", 10);
	Schrijfstruct(Hoofdmenu->Kring_2, sizeof (Rems_vent), "kring2.dat",10);
	Schrijfstruct(Hoofdmenu->Kring_3, sizeof (Rems_vent), "kring3.dat",10);
	Schrijfstruct(Hoofdmenu->Kring_4, sizeof (Rems_vent), "kring4.dat",10);
	Schrijfstruct(Hoofdmenu->Instelling, sizeof (ALR_inst), "alrinst.dat", 4);
	Schrijfstruct(&Voertuiggroep, sizeof (Groep), "voertgrp.dat", 1);
}
*/

void Schrijfdata(Menus * Hoofdmenu, char *filenaam)
{  int tel;
	Rems_vent Leeg = {0, 0, 0, ' ', 0, 0, 0, NULL, NULL, NULL};
	ALR_inst LeegALR = {"", "", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL};
	Berekeningsgegevens Gegevens;

	// De structure 'Gegevens' van het type 'Berekeningsgegevens' vullen met
	// de data van de afzonderlijke structures om het wegschrijven van alle
	// data van een berekening in een keer mogelijk te maken naar 1 file.
	Gegevens.Infogegevens = *Hoofdmenu->Info;
	Gegevens.Voertuiggegevens = *Hoofdmenu->Auto;

	// Structure 'Gegevens' wordt niet geinitialiseerd op nul waarden bij declaratie.
	for (tel=0; tel<10; tel++)
	{
		Gegevens.Kring1gegevens[tel] = Leeg;
		Gegevens.Kring2gegevens[tel] = Leeg;
		Gegevens.Kring3gegevens[tel] = Leeg;
		Gegevens.Kring4gegevens[tel] = Leeg;

		Gegevens.Kring1gegevens[tel] = Hoofdmenu->Kring_1[tel];
		Gegevens.Kring2gegevens[tel] = Hoofdmenu->Kring_2[tel];
		Gegevens.Kring3gegevens[tel] = Hoofdmenu->Kring_3[tel];
		Gegevens.Kring4gegevens[tel] = Hoofdmenu->Kring_4[tel];
	}
	for (tel=0; tel<4; tel++)
	{  Gegevens.ALRgegevens[tel] = LeegALR;
		Gegevens.ALRgegevens[tel] = Hoofdmenu->Instelling[tel];
	}
	Gegevens.Groepgegevens = Voertuiggroep;
	Schrijfstruct(&Gegevens, sizeof (Berekeningsgegevens), filenaam, 1);
}


// ======================================================================
void Leesdata(Menus * Hoofdmenu, char *filenaam)
{  int tel;
	Rems_vent Leeg = {0, 0, 0, ' ', 0, 0, 0, NULL, NULL, NULL};
	ALR_inst LeegALR = {"", "", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL};
	Berekeningsgegevens Gegevens;

	if(Leesstruct(&Gegevens, sizeof (Berekeningsgegevens), filenaam, 1))
	return;


	*Hoofdmenu->Info = Gegevens.Infogegevens;
	*Hoofdmenu->Auto = Gegevens.Voertuiggegevens;

	// Structure 'Gegevens' wordt niet geinitialiseerd op nul waarden bij declaratie.
	for (tel=0; tel<10; tel++)
	{
		Hoofdmenu->Kring_1[tel]	= Leeg;
		Hoofdmenu->Kring_2[tel]	= Leeg;
		Hoofdmenu->Kring_3[tel]	= Leeg;
		Hoofdmenu->Kring_4[tel]	= Leeg;

		Hoofdmenu->Kring_1[tel]	= Gegevens.Kring1gegevens[tel];
		Hoofdmenu->Kring_2[tel]	= Gegevens.Kring2gegevens[tel];
		Hoofdmenu->Kring_3[tel]	= Gegevens.Kring3gegevens[tel];
		Hoofdmenu->Kring_4[tel]	= Gegevens.Kring4gegevens[tel];
	}
	for (tel=0; tel<4; tel++)
	{	Hoofdmenu->Instelling[tel]	= LeegALR;
		Hoofdmenu->Instelling[tel]	= Gegevens.ALRgegevens[tel];
	}
	Voertuiggroep = Gegevens.Groepgegevens;
	Init_remschema(Hoofdmenu);
}
