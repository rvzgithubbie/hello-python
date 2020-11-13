#include "prototyp.h"
#include <dir.h>

void Menu_wijzb_XY (Menus *Hoofdmenu);
void Menu_wijzb_ALR(Menus *Hoofdmenu);
void Menu_wijzb_LL (Menus *Hoofdmenu);
void Menu_wijzb_VE (Menus *Hoofdmenu);
void Wijzig_XY_Rec (XY_vent *XY_pntr);
void Wijzig_ALR_Rec(ALR_vent *ALR_pntr);
void Wijzig_LL_Rec (LL_vent *LL_pntr);
void Wijzig_VE_Rec (Veerkar *VE_pntr);
void Afbeeld_XY (XY_vent *XY_pntr);
void Afbeeld_ALR (ALR_vent *ALR_pntr);
void Afbeeld_LL (LL_vent *LL_pntr);
void Afbeeld_VE (Veerkar *VE_pntr);
void Afbeeld_Voert (void);
Veerkar *Bepaal_Veerkar_adres(Veerkar *Tabel, int nummer);
void Opslaan_XY(Menus *Hoofdmenu);
void Opslaan_ALR(Menus *Hoofdmenu);
void Opslaan_LL(Menus *Hoofdmenu);
void Opslaan_VE(Menus *Hoofdmenu);

// =========== Menu voor diversen XY record =================================
void Menu_wijzb_XY(Menus *Hoofdmenu)
{	int tel, recnr=0, Unieknr=1000, hulp=0;
	char kar;
	char voettekst[7][20] = {"Pgup", "Pgdn", "Toevoegen","Wijzigen","Unieknr", "Opslaan", "Einde"};
	XY_vent *XY_pntr = &Hoofdmenu->XY_vent_Tabel[recnr];
	Unieknr = XY_pntr->nummer;

	clrscr();
	Kopgegevens();

	do
	{	Afbeeld_XY(XY_pntr);
		Voetmenu (voettekst, 7);
		kar = toupper (getch());
		if (kar == 0) kar = getch(); // Bij gebruik pgup pgdn

		switch (kar)
		{	case 73 :	// Page up, zoek vorige record
							if (recnr > 0)
							{	recnr--;
								XY_pntr = &Hoofdmenu->XY_vent_Tabel[recnr];
								Unieknr = XY_pntr->nummer;
							}
							break;
			case 81 :	// Page down, zoek volgende record
							if (recnr < 49)
							{	if (Hoofdmenu->XY_vent_Tabel[recnr+1].nummer != 0)
								{	recnr++;
									XY_pntr = &Hoofdmenu->XY_vent_Tabel[recnr];
									Unieknr = XY_pntr->nummer;
								}
							}
							break;
			case 'T' :	// Eerste record zoeken waarvan nummer==0
							tel=0;
							while (Hoofdmenu->XY_vent_Tabel[tel].nummer != 0 && tel < 49) tel++;
							if (tel==49)
							{	Boodschap ("XY bestand vol!");
								break;
							}
							XY_pntr = &Hoofdmenu->XY_vent_Tabel[tel];
							recnr = tel;
							if (tel>0) // Volgnummer toekennen aan nieuwe record
							XY_pntr->nummer = Hoofdmenu->XY_vent_Tabel[tel-1].nummer + 1;
							Unieknr = XY_pntr->nummer;
							Afbeeld_XY(XY_pntr);
							Wijzig_XY_Rec(XY_pntr);
							break;
			case 'U' :	// Unieknummer invoeren en bijbehorend record zoeken
							hulp = editveld(&Unieknr, 37, 6, 5);
							if (hulp != 27)
							{	if (Check_of_aanwezig(Unieknr, Hoofdmenu))
								{	Boodschap ("Unieknr. bestaat niet!");
									break;
								}
								if (Bepaal_ventieltype(Unieknr) == 'x')
								{	tel=0;
									XY_pntr = Bepaal_XY_adres(Hoofdmenu->XY_vent_Tabel, Unieknr);
									Unieknr = XY_pntr->nummer;
									// Bijbehorend recordnr zoeken
									while (Hoofdmenu->XY_vent_Tabel[tel].nummer != Unieknr && tel < 49) tel++;
									recnr=tel;
								}
								else
								{	Boodschap ("Unieknr. niet van XY ventiel!");
									break;
								}
							}
							break;
			case 'W' :	Wijzig_XY_Rec(XY_pntr);
							break;
			case 'O' :	Opslaan_XY(Hoofdmenu);
							break;
			default: 	break;
		}
	}while (kar != 'E' && kar != 13 && kar != 27 && kar != 32);
}

// ========== Menu voor diversen ALR record =================================
void Menu_wijzb_ALR(Menus *Hoofdmenu)
{	int tel, recnr=0, Unieknr=2000, hulp=0;
	char kar, ALR_type;
	char voettekst[7][20] = {"Pgup", "Pgdn", "Toevoegen","Wijzigen","Unieknr", "Opslaan", "Einde"};
	ALR_vent *ALR_pntr = &Hoofdmenu->ALR_vent_Tabel[recnr];
	Unieknr = ALR_pntr->nummer;

	clrscr();
	Kopgegevens();

	do
	{	Afbeeld_ALR(ALR_pntr);
		Voetmenu (voettekst, 7);
		kar = toupper (getch());
		if (kar == 0) kar = getch(); // Bij gebruik pgup pgdn

		switch (kar)
		{	case 73 :	// Page up, zoek vorige record
							if (recnr > 0)
							{	recnr--;
								ALR_pntr = &Hoofdmenu->ALR_vent_Tabel[recnr];
								Unieknr = ALR_pntr->nummer;
							}
							break;
			case 81 :	// Page down, zoek volgende record
							if (recnr < 24)
							{	if (Hoofdmenu->ALR_vent_Tabel[recnr+1].nummer != 0)
								{	recnr++;
									ALR_pntr = &Hoofdmenu->ALR_vent_Tabel[recnr];
									Unieknr = ALR_pntr->nummer;
								}
							}
							break;
			case 'T' :	// Eerste record zoeken waarvan nummer==0
							tel=0;
							while (Hoofdmenu->ALR_vent_Tabel[tel].nummer != 0 && tel < 24) tel++;
							if (tel==49)
							{	Boodschap ("ALR bestand vol!");
								break;
							}
							ALR_pntr = &Hoofdmenu->ALR_vent_Tabel[tel];
							recnr = tel;

							Window b = {"Selectie ALR TYPE",
							20,10,60,13, WHITE, BLUE, DOUBLE_BORDER, CENTER_TITLE};
							char *Wintekst [] = {"ALR zonder variabele insprong",
														"Met variabele insprong",
														NULL};
							NewWindow(&b);
							ALR_type = Keuzewindow(&b, Wintekst);
							CloseWindow(&b);
							Unieknr = 0;
							tel = 0;
							if (ALR_type == 0)  // alr zonder var. insprong (2000 nr.)
							{	while (Hoofdmenu->ALR_vent_Tabel[tel].nummer != 0 && tel < 25)
								{	if (Bepaal_ventieltype(Hoofdmenu->ALR_vent_Tabel[tel].nummer) == 'a')
									Unieknr = Hoofdmenu->ALR_vent_Tabel[tel].nummer;
									tel++;
								}
								if (Unieknr == 0) Unieknr = 2000;
								else Unieknr++;
							}
							else  // alr met var. inspring (4000 nr.)
							{	while (Hoofdmenu->ALR_vent_Tabel[tel].nummer != 0 && tel < 25)
								{	if (Bepaal_ventieltype(Hoofdmenu->ALR_vent_Tabel[tel].nummer) == 'i')
									Unieknr = Hoofdmenu->ALR_vent_Tabel[tel].nummer;
									tel++;
								}
								if (Unieknr == 0) Unieknr = 4000;
								else Unieknr++;
							}
							// Volgnummer toekennen aan nieuwe record
							ALR_pntr->nummer = Unieknr;
							Afbeeld_ALR(ALR_pntr);
							Wijzig_ALR_Rec(ALR_pntr);
							break;
			case 'U' :	// Unieknummer invoeren en bijbehorend record zoeken
							hulp = editveld(&Unieknr, 57, 5, 5);
							if (hulp != 27)
							{	if (Check_of_aanwezig(Unieknr, Hoofdmenu))
								{	Boodschap ("Unieknr. bestaat niet!");
									break;
								}
								if (Bepaal_ventieltype(Unieknr) == 'a' ||
									 Bepaal_ventieltype(Unieknr) == 'i')
								{	tel=0;
									ALR_pntr = Bepaal_ALR_adres(Hoofdmenu->ALR_vent_Tabel, Unieknr);
									Unieknr = ALR_pntr->nummer;
									// Bijbehorend recordnr zoeken
									while (Hoofdmenu->ALR_vent_Tabel[tel].nummer != Unieknr && tel < 24) tel++;
									recnr=tel;
								}
								else
								{	Boodschap ("Unieknr. niet van ALR ventiel!");
									break;
								}
							}
							break;
			case 'W' :	Wijzig_ALR_Rec(ALR_pntr);
							break;
			case 'O' :	Opslaan_ALR(Hoofdmenu);
							break;
			default: 	break;
		}
	}while (kar != 'E' && kar != 13 && kar != 27 && kar != 32);
}

// =========== Menu voor diversen LL record =================================
void Menu_wijzb_LL(Menus *Hoofdmenu)
{	int tel, recnr=0, Unieknr=3000, hulp=0;
	char kar;
	char voettekst[7][20] = {"Pgup", "Pgdn", "Toevoegen","Wijzigen","Unieknr", "Opslaan", "Einde"};
	LL_vent *LL_pntr = &Hoofdmenu->LL_vent_Tabel[recnr];
	Unieknr = LL_pntr->nummer;

	clrscr();
	Kopgegevens();

	do
	{	Afbeeld_LL(LL_pntr);
		Voetmenu (voettekst, 7);
		kar = toupper (getch());
		if (kar == 0) kar = getch(); // Bij gebruik pgup pgdn

		switch (kar)
		{	case 73 :	// Page up, zoek vorige record
							if (recnr > 0)
							{	recnr--;
								LL_pntr = &Hoofdmenu->LL_vent_Tabel[recnr];
								Unieknr = LL_pntr->nummer;
							}
							break;
			case 81 :	// Page down, zoek volgende record
							if (recnr < 24)
							{	if (Hoofdmenu->LL_vent_Tabel[recnr+1].nummer != 0)
								{	recnr++;
									LL_pntr = &Hoofdmenu->LL_vent_Tabel[recnr];
									Unieknr = LL_pntr->nummer;
								}
							}
							break;
			case 'T' :	// Eerste record zoeken waarvan nummer==0
							tel=0;
							while (Hoofdmenu->LL_vent_Tabel[tel].nummer != 0 && tel < 24) tel++;
							if (tel==24)
							{	Boodschap ("LastLeer bestand vol!");
								break;
							}
							LL_pntr = &Hoofdmenu->LL_vent_Tabel[tel];
							recnr = tel;

							if (tel>0) // Volgnummer toekennen aan nieuwe record
							LL_pntr->nummer = Hoofdmenu->LL_vent_Tabel[tel-1].nummer + 1;
							Unieknr = LL_pntr->nummer;
							Afbeeld_LL(LL_pntr);
							Wijzig_LL_Rec(LL_pntr);
							break;
			case 'U' :	// Unieknummer invoeren en bijbehorend record zoeken
							hulp = editveld(&Unieknr, 37, 6, 5);
							if (hulp != 27)
							{	if (Check_of_aanwezig(Unieknr, Hoofdmenu))
								{	Boodschap ("Unieknr. bestaat niet!");
									break;
								}
								if (Bepaal_ventieltype(Unieknr) == 'l')
								{	tel=0;
									LL_pntr = Bepaal_LL_adres(Hoofdmenu->LL_vent_Tabel, Unieknr);
									Unieknr = LL_pntr->nummer;
									// Bijbehorend recordnr zoeken
									while (Hoofdmenu->LL_vent_Tabel[tel].nummer != Unieknr && tel < 24) tel++;
									recnr=tel;
								}
								else
								{	Boodschap ("Unieknr. niet van LastLeer ventiel!");
									break;
								}
							}
							break;
			case 'W' :	Wijzig_LL_Rec(LL_pntr);
							break;
			case 'O' :	Opslaan_LL(Hoofdmenu);
							break;
			default: 	break;
		}
	}while (kar != 'E' && kar != 13 && kar != 27 && kar != 32);
}

// =========== Menu voor diversen Veerkar record =================================
void Menu_wijzb_VE(Menus *Hoofdmenu)
{	int tel, recnr=0, Unieknr=9000, hulp=0;
	char kar;
	char voettekst[7][20] = {"Pgup", "Pgdn", "Toevoegen","Wijzigen","Unieknr", "Opslaan", "Einde"};
	Veerkar *VE_pntr = &Hoofdmenu->Veerkar_Tabel[recnr];
	Unieknr = VE_pntr->nummer;

	clrscr();
	Kopgegevens();

	do
	{	Afbeeld_VE(VE_pntr);
		Voetmenu (voettekst, 7);
		kar = toupper (getch());
		if (kar == 0) kar = getch(); // Bij gebruik pgup pgdn

		switch (kar)
		{	case 73 :	// Page up, zoek vorige record
							if (recnr > 0)
							{	recnr--;
								VE_pntr = &Hoofdmenu->Veerkar_Tabel[recnr];
								Unieknr = VE_pntr->nummer;
							}
							break;
			case 81 :	// Page down, zoek volgende record
							if (recnr < 24)
							{	if (Hoofdmenu->Veerkar_Tabel[recnr+1].nummer != 0)
								{	recnr++;
									VE_pntr = &Hoofdmenu->Veerkar_Tabel[recnr];
									Unieknr = VE_pntr->nummer;
								}
							}
							break;
			case 'T' :	// Eerste record zoeken waarvan nummer==0
							tel=0;
							while (Hoofdmenu->Veerkar_Tabel[tel].nummer != 0 && tel < 24) tel++;
							if (tel==24)
							{	Boodschap ("Veerkar bestand vol!");
								break;
							}
							VE_pntr = &Hoofdmenu->Veerkar_Tabel[tel];
							recnr = tel;

							if (tel>0) // Volgnummer toekennen aan nieuwe record
							VE_pntr->nummer = Hoofdmenu->Veerkar_Tabel[tel-1].nummer + 1;
							Unieknr = VE_pntr->nummer;
							Afbeeld_VE(VE_pntr);
							Wijzig_VE_Rec(VE_pntr);
							break;
			case 'U' :	// Unieknummer invoeren en bijbehorend record zoeken
							hulp = editveld(&Unieknr, 37, 6, 5);
							if (hulp != 27)
							{	if (Check_of_aanwezig(Unieknr, Hoofdmenu))
								{	Boodschap ("Unieknr. bestaat niet!");
									break;
								}
								if (Bepaal_ventieltype(Unieknr) == 'v')
								{	tel=0;
									VE_pntr = Bepaal_Veerkar_adres(Hoofdmenu->Veerkar_Tabel, Unieknr);
									Unieknr = VE_pntr->nummer;
									// Bijbehorend recordnr zoeken
									while (Hoofdmenu->Veerkar_Tabel[tel].nummer != Unieknr && tel < 24) tel++;
									recnr=tel;
								}
								else
								{	Boodschap ("Unieknr. niet van Veerkarakteristiek");
									break;
								}
							}
							break;
			case 'W' :	Wijzig_VE_Rec(VE_pntr);
							break;
			case 'O' :	Opslaan_VE(Hoofdmenu);
							break;
			default: 	break;
		}
	}while (kar != 'E' && kar != 13 && kar != 27 && kar != 32);
}

// ======================== Wijzigen XY record ============================
void Wijzig_XY_Rec(XY_vent *XY_pntr)
{  int tel, hulp=0;
	char voettekst[3][20] = {"Esc=opheffen", "Pgdn=stop","Enter=doorgaan"};

	Afbeeld_XY(XY_pntr);
	Voetmenu (voettekst, 3);

	tel=1;
	while (tel<24 && hulp!=27 && hulp != 81)
	{	switch (tel)
		{	case  1:	break;
			case  2:	hulp = editveld(XY_pntr->omschr, 37, 7, 30); break;
			case  3:	hulp = editveld(XY_pntr->bestelnr,  37, 8, 20); break;
			case  4:	hulp = editveld(&XY_pntr->waarden[0][0], 10, 12, 7, 2); break;
			case  5:	hulp = editveld(&XY_pntr->waarden[0][1], 20, 12, 7, 2); break;
			case  6:	hulp = editveld(&XY_pntr->waarden[1][0], 10, 13, 7, 2); break;
			case  7:	hulp = editveld(&XY_pntr->waarden[1][1], 20, 13, 7, 2); break;
			case  8:	hulp = editveld(&XY_pntr->waarden[2][0], 10, 14, 7, 2); break;
			case  9:	hulp = editveld(&XY_pntr->waarden[2][1], 20, 14, 7, 2); break;
			case 10:	hulp = editveld(&XY_pntr->waarden[3][0], 10, 15, 7, 2); break;
			case 11:	hulp = editveld(&XY_pntr->waarden[3][1], 20, 15, 7, 2); break;
			case 12:	hulp = editveld(&XY_pntr->waarden[4][0], 10, 16, 7, 2); break;
			case 13:	hulp = editveld(&XY_pntr->waarden[4][1], 20, 16, 7, 2); break;
			case 14:	hulp = editveld(&XY_pntr->waarden[5][0], 10, 17, 7, 2); break;
			case 15:	hulp = editveld(&XY_pntr->waarden[5][1], 20, 17, 7, 2); break;
			case 16:	hulp = editveld(&XY_pntr->waarden[6][0], 10, 18, 7, 2); break;
			case 17:	hulp = editveld(&XY_pntr->waarden[6][1], 20, 18, 7, 2); break;
			case 18:	hulp = editveld(&XY_pntr->waarden[7][0], 10, 19, 7, 2); break;
			case 19:	hulp = editveld(&XY_pntr->waarden[7][1], 20, 19, 7, 2); break;
			case 20:	hulp = editveld(&XY_pntr->waarden[8][0], 10, 20, 7, 2); break;
			case 21:	hulp = editveld(&XY_pntr->waarden[8][1], 20, 20, 7, 2); break;
			case 22:	hulp = editveld(&XY_pntr->waarden[9][0], 10, 21, 7, 2); break;
			case 23:	hulp = editveld(&XY_pntr->waarden[9][1], 20, 21, 7, 2); break;
			default: break;
		}
		if (hulp == 72 && tel>1) tel--;
		else tel++;
	}
}

// ======================== Wijzigen ALR record ============================
void Wijzig_ALR_Rec(ALR_vent *ALR_pntr)
{  int tel, hulp=0;
	char voettekst[3][20] = {"Esc=opheffen", "Pgdn=stop","Enter=doorgaan"};
	char DYN_STAT[3] = "  ";
	char MECH_PNEUM[3] = "  ";

	DYN_STAT[0] = ALR_pntr->dyn_stat;
	MECH_PNEUM[0] = ALR_pntr->mech_pneum;

	Voetmenu (voettekst, 3);

	tel=1;
	while (tel<47 && hulp!=27 && hulp != 81)
	{	switch (tel)
		{	case  1:	break;
			case  2:	hulp = editveld(DYN_STAT, 37, 5, 2);
						ALR_pntr->dyn_stat = DYN_STAT[0];
						if (DYN_STAT[0] != 'd' && DYN_STAT[0] != 's')
						{	Boodschap("Foutieve invoer!");
							tel--;
						}
						break;
			case  3:	hulp = editveld(MECH_PNEUM, 37, 6, 2);
						ALR_pntr->mech_pneum = MECH_PNEUM[0];
						if (MECH_PNEUM[0] != 'm' && MECH_PNEUM[0] != 'p')
						{	Boodschap("Foutieve invoer!");
							tel--;
						}
						break;
			case  4:	hulp = editveld(ALR_pntr->omschr, 37, 7, 30); break;
			case  5:	hulp = editveld(ALR_pntr->bestelnr,  37, 8, 20); break;
			case  6:	hulp = editveld(&ALR_pntr->Pkar,  34, 9, 7, 2); break;
			case  7:	hulp = editveld(&ALR_pntr->Stuurkar[0][0], 10, 12, 7, 2); break;
			case  8:	hulp = editveld(&ALR_pntr->Stuurkar[0][1], 20, 12, 7, 2); break;
			case  9:	hulp = editveld(&ALR_pntr->Stuurkar[1][0], 10, 13, 7, 2); break;
			case 10:	hulp = editveld(&ALR_pntr->Stuurkar[1][1], 20, 13, 7, 2); break;
			case 11:	hulp = editveld(&ALR_pntr->Stuurkar[2][0], 10, 14, 7, 2); break;
			case 12:	hulp = editveld(&ALR_pntr->Stuurkar[2][1], 20, 14, 7, 2); break;
			case 13:	hulp = editveld(&ALR_pntr->Stuurkar[3][0], 10, 15, 7, 2); break;
			case 14:	hulp = editveld(&ALR_pntr->Stuurkar[3][1], 20, 15, 7, 2); break;
			case 15:	hulp = editveld(&ALR_pntr->Stuurkar[4][0], 10, 16, 7, 2); break;
			case 16:	hulp = editveld(&ALR_pntr->Stuurkar[4][1], 20, 16, 7, 2); break;
			case 17:	hulp = editveld(&ALR_pntr->Stuurkar[5][0], 10, 17, 7, 2); break;
			case 18:	hulp = editveld(&ALR_pntr->Stuurkar[5][1], 20, 17, 7, 2); break;
			case 19:	hulp = editveld(&ALR_pntr->Stuurkar[6][0], 10, 18, 7, 2); break;
			case 20:	hulp = editveld(&ALR_pntr->Stuurkar[6][1], 20, 18, 7, 2); break;
			case 21:	hulp = editveld(&ALR_pntr->Stuurkar[7][0], 10, 19, 7, 2); break;
			case 22:	hulp = editveld(&ALR_pntr->Stuurkar[7][1], 20, 19, 7, 2); break;
			case 23:	hulp = editveld(&ALR_pntr->Stuurkar[8][0], 10, 20, 7, 2); break;
			case 24:	hulp = editveld(&ALR_pntr->Stuurkar[8][1], 20, 20, 7, 2); break;
			case 25:	hulp = editveld(&ALR_pntr->Stuurkar[9][0], 10, 21, 7, 2); break;
			case 26:	hulp = editveld(&ALR_pntr->Stuurkar[9][1], 20, 21, 7, 2); break;
			case 27:	hulp = editveld(&ALR_pntr->In_uit[0][0], 50, 12, 7, 2); break;
			case 28:	hulp = editveld(&ALR_pntr->In_uit[0][1], 60, 12, 7, 2); break;
			case 29:	hulp = editveld(&ALR_pntr->In_uit[1][0], 50, 13, 7, 2); break;
			case 30:	hulp = editveld(&ALR_pntr->In_uit[1][1], 60, 13, 7, 2); break;
			case 31:	hulp = editveld(&ALR_pntr->In_uit[2][0], 50, 14, 7, 2); break;
			case 32:	hulp = editveld(&ALR_pntr->In_uit[2][1], 60, 14, 7, 2); break;
			case 33:	hulp = editveld(&ALR_pntr->In_uit[3][0], 50, 15, 7, 2); break;
			case 34:	hulp = editveld(&ALR_pntr->In_uit[3][1], 60, 15, 7, 2); break;
			case 35:	hulp = editveld(&ALR_pntr->In_uit[4][0], 50, 16, 7, 2); break;
			case 36:	hulp = editveld(&ALR_pntr->In_uit[4][1], 60, 16, 7, 2); break;
			case 37:	hulp = editveld(&ALR_pntr->In_uit[5][0], 50, 17, 7, 2); break;
			case 38:	hulp = editveld(&ALR_pntr->In_uit[5][1], 60, 17, 7, 2); break;
			case 39:	hulp = editveld(&ALR_pntr->In_uit[6][0], 50, 18, 7, 2); break;
			case 40:	hulp = editveld(&ALR_pntr->In_uit[6][1], 60, 18, 7, 2); break;
			case 41:	hulp = editveld(&ALR_pntr->In_uit[7][0], 50, 19, 7, 2); break;
			case 42:	hulp = editveld(&ALR_pntr->In_uit[7][1], 60, 19, 7, 2); break;
			case 43:	hulp = editveld(&ALR_pntr->In_uit[8][0], 50, 20, 7, 2); break;
			case 44:	hulp = editveld(&ALR_pntr->In_uit[8][1], 60, 20, 7, 2); break;
			case 45:	hulp = editveld(&ALR_pntr->In_uit[9][0], 50, 21, 7, 2); break;
			case 46:	hulp = editveld(&ALR_pntr->In_uit[9][1], 60, 21, 7, 2); break;
			default: break;
		}
		if (hulp == 72 && tel>1) tel--;
		else tel++;
	}
}

// ======================== Wijzigen LL record ============================
void Wijzig_LL_Rec(LL_vent *LL_pntr)
{  int tel, hulp=0;
	char voettekst[3][20] = {"Esc=opheffen", "Pgdn=stop","Enter=doorgaan"};

	Voetmenu (voettekst, 3);

	tel=1;
	while (tel<9 && hulp!=27 && hulp != 81)
	{	switch (tel)
		{	case  1:	break;
			case  2:	hulp = editveld(LL_pntr->omschr, 37, 7, 30); break;
			case  3:	hulp = editveld(LL_pntr->bestelnr, 37, 8, 20); break;
			case  4:	hulp = editveld(&LL_pntr->Paanspr, 37, 9,  7, 2); break;
			case  5:	hulp = editveld(&LL_pntr->Pnood,   37, 10, 7, 2); break;
			case  6: hulp = editveld(&LL_pntr->Pinspr,  37, 11, 7, 2); break;
			case  7:	hulp = editveld(&LL_pntr->P1_fact, 37, 12, 7, 2); break;
			case  8:	hulp = editveld(&LL_pntr->P4_fact, 37, 13, 7, 2); break;
			default: break;
		}
		if (hulp == 72 && tel>1) tel--;
		else tel++;
	}
}

// ======================== Wijzigen Veerkar record ============================
void Wijzig_VE_Rec(Veerkar *VE_pntr)
{  int tel, hulp=0;
	char voettekst[3][20] = {"Esc=opheffen", "Pgdn=stop","Enter=doorgaan"};

	Voetmenu (voettekst, 3);

	tel=1;
	while (tel<24 && hulp!=27 && hulp != 81)
	{	switch (tel)
		{	case  1:	break;
			case  2:	hulp = editveld(VE_pntr->omschr, 37, 7, 30); break;
			case  3:	hulp = editveld(VE_pntr->bestelnr,  37, 8, 20); break;
			case  4:	hulp = editveld(&VE_pntr->waarden[0][0], 10, 12, 10, 2); break;
			case  5:	hulp = editveld(&VE_pntr->waarden[0][1], 20, 12, 7, 2); break;
			case  6:	hulp = editveld(&VE_pntr->waarden[1][0], 10, 13, 10, 2); break;
			case  7:	hulp = editveld(&VE_pntr->waarden[1][1], 20, 13, 7, 2); break;
			case  8:	hulp = editveld(&VE_pntr->waarden[2][0], 10, 14, 10, 2); break;
			case  9:	hulp = editveld(&VE_pntr->waarden[2][1], 20, 14, 7, 2); break;
			case 10:	hulp = editveld(&VE_pntr->waarden[3][0], 10, 15, 10, 2); break;
			case 11:	hulp = editveld(&VE_pntr->waarden[3][1], 20, 15, 7, 2); break;
			case 12:	hulp = editveld(&VE_pntr->waarden[4][0], 10, 16, 10, 2); break;
			case 13:	hulp = editveld(&VE_pntr->waarden[4][1], 20, 16, 7, 2); break;
			case 14:	hulp = editveld(&VE_pntr->waarden[5][0], 10, 17, 10, 2); break;
			case 15:	hulp = editveld(&VE_pntr->waarden[5][1], 20, 17, 7, 2); break;
			case 16:	hulp = editveld(&VE_pntr->waarden[6][0], 10, 18, 10, 2); break;
			case 17:	hulp = editveld(&VE_pntr->waarden[6][1], 20, 18, 7, 2); break;
			case 18:	hulp = editveld(&VE_pntr->waarden[7][0], 10, 19, 10, 2); break;
			case 19:	hulp = editveld(&VE_pntr->waarden[7][1], 20, 19, 7, 2); break;
			case 20:	hulp = editveld(&VE_pntr->waarden[8][0], 10, 20, 10, 2); break;
			case 21:	hulp = editveld(&VE_pntr->waarden[8][1], 20, 20, 7, 2); break;
			case 22:	hulp = editveld(&VE_pntr->waarden[9][0], 10, 21, 10, 2); break;
			case 23:	hulp = editveld(&VE_pntr->waarden[9][1], 20, 21, 7, 2); break;
			default: break;
		}
		if (hulp == 72 && tel>1) tel--;
		else tel++;
	}
}

//=========================== Afbeelden XY ventiel gegevens ===============
void Afbeeld_XY (XY_vent *XY_pntr)
{	int tel, tel2;
	_setcursortype(_NOCURSOR);
	for (tel=4; tel<22; tel++)
	{	gotoxy(1,tel); 
		clreol();
	}

	textcolor(LIGHTGRAY);
	gotoxy(1,6); cprintf ("Uniek nr. .......................");
	gotoxy(1,7); cprintf ("Omschrijving.....................");
	gotoxy(1,8); cprintf ("Bestelnummer.....................");
	gotoxy(1,11); cprintf ("            Pin      Puit");

	textcolor(GREEN);
	gotoxy(1,4);  cprintf ("XY_record in geheugen");
	gotoxy(1,10); cprintf ("           XY karakteristiek");

	textcolor (WHITE);
	gotoxy(37, 6); cprintf ("%5d",XY_pntr->nummer);
	gotoxy(37, 7); cprintf ("%s",XY_pntr->omschr);
	gotoxy(37, 8); cprintf ("%s",XY_pntr->bestelnr);

	for (tel=0; tel<2; tel++)
	{	for (tel2=0; tel2<10; tel2++)
		{	if(tel==0)
			{	gotoxy(11,12+tel2); cprintf ("%6.2f",XY_pntr->waarden[tel2][tel]);
			}
			if(tel==1)
			{	gotoxy(21,12+tel2); cprintf ("%6.2f",XY_pntr->waarden[tel2][tel]);
			}
		}
	}
	textcolor(LIGHTGRAY);
	_setcursortype(_NORMALCURSOR);
}

// ================== Afbeelden ALR ventiel record =========================
void Afbeeld_ALR (ALR_vent *ALR_pntr)
{	int tel, tel2;
	char type = Bepaal_ventieltype(ALR_pntr->nummer);
	_setcursortype(_NOCURSOR);
	for (tel=4; tel<22; tel++)
	{	gotoxy(1,tel);
		clreol();
	}

	textcolor(LIGHTGRAY);
	gotoxy(1,5); cprintf ("Regeling   (d=dyn    s=statisch).");
	gotoxy(45,5);cprintf ("Uniek nr. :");
	gotoxy(1,6); cprintf ("Aansturing (m=mech   p=pneum)....");
	gotoxy(1,7); cprintf ("Omschrijving.....................");
	gotoxy(1,8); cprintf ("Bestelnummer.....................");
	gotoxy(1,9); cprintf ("Karakteristieke druk.............           [bar]");
	if (type == 'a') 	{gotoxy(1,11); cprintf ("      ALR_hoek/Pbalg  Puit(Pin=Pkar)                Pin       Puit [bar]");}
	else 					{gotoxy(1,11); cprintf ("      Invering/Pbalg  Pinsprong                     Pin       Puit [bar]");}

	textcolor(GREEN);
	gotoxy(1,4);  cprintf ("ALR ventiel record in geheugen");
	if (type == 'a') 	{gotoxy(1,10); cprintf ("           Stuurkarakteristiek        Pin-Puit karakteristiek t/m knikpunt");}
	else					{gotoxy(1,10); cprintf ("           Stuurkarakteristiek        Pin-Puit volledige kar. (Pi = min.)");}

	textcolor (WHITE);
	gotoxy(57, 5); cprintf ("%5d", ALR_pntr->nummer);
	gotoxy(34, 5); cprintf ("%4c",ALR_pntr->dyn_stat);
	gotoxy(34, 6); cprintf ("%4c",ALR_pntr->mech_pneum);
	gotoxy(37, 7); cprintf ("%s",ALR_pntr->omschr);
	gotoxy(37, 8); cprintf ("%s",ALR_pntr->bestelnr);
	gotoxy(35, 9); cprintf ("%6.2f",ALR_pntr->Pkar);

	for (tel=0; tel<2; tel++)
	{	for (tel2=0; tel2<10; tel2++)
		{	if(tel==0)
			{	gotoxy(11,12+tel2); cprintf ("%6.2f",ALR_pntr->Stuurkar[tel2][tel]);
				gotoxy(51,12+tel2); cprintf ("%6.2f",ALR_pntr->In_uit[tel2][tel]);
			}
			if(tel==1)
			{	gotoxy(21,12+tel2); cprintf ("%6.2f",ALR_pntr->Stuurkar[tel2][tel]);
				gotoxy(61,12+tel2); cprintf ("%6.2f",ALR_pntr->In_uit[tel2][tel]);
			}
		}
	}
	textcolor(LIGHTGRAY);
	_setcursortype(_NORMALCURSOR);
}

// ============================= Afbeelden LL ventiel ======================
void Afbeeld_LL (LL_vent *LL_pntr)
{	int tel;
	_setcursortype(_NOCURSOR);
	for (tel=4; tel<22; tel++)
	{	gotoxy(1,tel);
		clreol();
	}

	textcolor(LIGHTGRAY);
	gotoxy(1, 6); cprintf ("Uniek nr. .......................");
	gotoxy(1, 7); cprintf ("Omschrijving.....................");
	gotoxy(1, 8); cprintf ("Bestelnummer.....................");
	gotoxy(1, 9); cprintf ("Aanspreekdruk....................           [bar]");
	gotoxy(1,10); cprintf ("Pnood   (als P4<=Pnood: P2=P1)...           [bar]");
	gotoxy(1,11); cprintf ("Pinsprong (Puit=Pin).............           [bar]");
	gotoxy(1,12); cprintf ("P1_factor........................            []");
	gotoxy(1,13); cprintf ("P4_factor........................            []");
	gotoxy(1,15); cprintf ("Puit = P1_fact * Pin + P4_fact * P4 - Paanspr");
	textcolor(GREEN);
	gotoxy(1,4);  cprintf ("LastLeer ventiel record in geheugen");

	textcolor (WHITE);
	gotoxy(37, 6); cprintf ("%5d", LL_pntr->nummer);
	gotoxy(37, 7); cprintf ("%s", LL_pntr->omschr);
	gotoxy(37, 8); cprintf ("%s", LL_pntr->bestelnr);
	gotoxy(38, 9); cprintf ("%6.2f", LL_pntr->Paanspr);
	gotoxy(38,10); cprintf ("%6.2f", LL_pntr->Pnood);
	gotoxy(38,11); cprintf ("%6.2f", LL_pntr->Pinspr);
	gotoxy(38,12); cprintf ("%6.2f", LL_pntr->P1_fact);
	gotoxy(38,13); cprintf ("%6.2f", LL_pntr->P4_fact);

	textcolor(LIGHTGRAY);
	_setcursortype(_NORMALCURSOR);
}

// ============================= Afbeelden veerkarakteristiek ===============
void Afbeeld_VE (Veerkar *VE_pntr)
{	int tel, tel2;
	_setcursortype(_NOCURSOR);
	for (tel=4; tel<22; tel++)
	{	gotoxy(1,tel); 
		clreol();
	}

	textcolor(LIGHTGRAY);
	gotoxy(1,6); cprintf ("Uniek nr. .......................");
	gotoxy(1,7); cprintf ("Omschrijving.....................");
	gotoxy(1,8); cprintf ("Referentie.......................");
	gotoxy(1,11); cprintf ("          Aslast[kg] Veerweg/Pbalg/Pinsprong [mm]/[bar]/[bar]");

	textcolor(GREEN);
	gotoxy(1,4);  cprintf ("Veerkarakteristiek record in geheugen");
	gotoxy(1,10); cprintf ("          Veerkarakteristiek");

	textcolor (WHITE);
	gotoxy(37, 6); cprintf ("%5d", VE_pntr->nummer);
	gotoxy(37, 7); cprintf ("%s",VE_pntr->omschr);
	gotoxy(37, 8); cprintf ("%s",VE_pntr->bestelnr);

	for (tel=0; tel<2; tel++)
	{	for (tel2=0; tel2<10; tel2++)
		{	if(tel==0)
			{	gotoxy(11,12+tel2); cprintf ("%9.2f",VE_pntr->waarden[tel2][tel]);
			}
			if(tel==1)
			{	gotoxy(21,12+tel2); cprintf ("%6.2f",VE_pntr->waarden[tel2][tel]);
			}
		}
	}
	textcolor(LIGHTGRAY);
	_setcursortype(_NORMALCURSOR);
}

// ======================== Retourneert het adres van het veerkar ==========
Veerkar *Bepaal_Veerkar_adres(Veerkar *Tabel, int nummer)
{	int tel=0;
	while (Tabel[tel].nummer != nummer && tel < 25) tel++;
	return &Tabel[tel];
}

// ======================== opslaan XY tabel ===============================
void Opslaan_XY(Menus *Hoofdmenu)
{	int tel, tel2, controle=0;
	FILE *stream = NULL;

	remove("xy_vent.bak");
	if (rename("xy_vent.dat", "xy_vent.bak") == 0) controle=1;
	else Boodschap("Fout in creeren backup file XY_VENT.BAK of .DAT file niet gevonden!");

	if (controle)
	{	if ((stream = fopen("xy_vent.dat", "wt")) != NULL)
		{	fseek(stream, 0, SEEK_SET);
			for (tel=0; tel<50; tel++)
			{	fprintf (stream, "|%4d |%-30s|%-20s|",
									Hoofdmenu->XY_vent_Tabel[tel].nummer,
									Hoofdmenu->XY_vent_Tabel[tel].omschr,
									Hoofdmenu->XY_vent_Tabel[tel].bestelnr);
				for (tel2=0; tel2<10; tel2++)
				{	fprintf (stream, "%6.2f|%6.2f|",
									Hoofdmenu->XY_vent_Tabel[tel].waarden[tel2][0],
									Hoofdmenu->XY_vent_Tabel[tel].waarden[tel2][1]);
				}
				fprintf (stream, "\n");
			}
			fclose (stream);
		}
		else Boodschap ("Fout in openen van bestand XY_VENT.DAT !");
	}
}

// ======================== opslaan ALR tabel ===============================
void Opslaan_ALR(Menus *Hoofdmenu)
{	int tel, tel2, controle=0;
	FILE *stream = NULL;

	remove("alr_vent.bak");
	if (rename("alr_vent.dat", "alr_vent.bak") == 0) controle=1;
	else Boodschap("Fout in creeren backup file ALR_VENT.BAK of .DAT file niet gevonden!");

	if (controle)
	{	if ((stream = fopen("alr_vent.dat", "wt")) != NULL)
		{	fseek(stream, 0, SEEK_SET);
			for (tel=0; tel<25; tel++)
			{	fprintf (stream, "|%4d |%c|%c|%-30s|%-20s|%6.2f|",
									Hoofdmenu->ALR_vent_Tabel[tel].nummer,
									Hoofdmenu->ALR_vent_Tabel[tel].dyn_stat,
									Hoofdmenu->ALR_vent_Tabel[tel].mech_pneum,
									Hoofdmenu->ALR_vent_Tabel[tel].omschr,
									Hoofdmenu->ALR_vent_Tabel[tel].bestelnr,
									Hoofdmenu->ALR_vent_Tabel[tel].Pkar);
				for (tel2=0; tel2<10; tel2++)
				{	fprintf (stream, "%6.2f|%6.2f|",
									Hoofdmenu->ALR_vent_Tabel[tel].In_uit[tel2][0],
									Hoofdmenu->ALR_vent_Tabel[tel].In_uit[tel2][1]);
				}
				fprintf (stream, "\n|");

				for (tel2=0; tel2<10; tel2++)
				{	fprintf (stream, "%6.2f|%6.2f|",
									Hoofdmenu->ALR_vent_Tabel[tel].Stuurkar[tel2][0],
									Hoofdmenu->ALR_vent_Tabel[tel].Stuurkar[tel2][1]);
				}
				fprintf (stream, "\n");
			}
			fclose (stream);
		}
		else Boodschap ("Fout in openen van bestand ALR_VENT.DAT !");
	}
}
// ======================== opslaan LL tabel ===============================
void Opslaan_LL(Menus *Hoofdmenu)
{	int tel, controle=0;
	FILE *stream = NULL;

	remove("ll_vent.bak");
	if (rename("ll_vent.dat", "ll_vent.bak") == 0) controle=1;
	else Boodschap("Fout in creeren backup file LL_VENT.BAK of .DAT file niet gevonden!");

	if (controle)
	{	if ((stream = fopen("ll_vent.dat", "wt")) != NULL)
		{	fseek(stream, 0, SEEK_SET);
			for (tel=0; tel<25; tel++)
			{	fprintf (stream, "|%4d |%-30s|%-20s|%6.2f|%6.2f|%6.2f|%6.2f|%6.2f|\n",
									Hoofdmenu->LL_vent_Tabel[tel].nummer,
									Hoofdmenu->LL_vent_Tabel[tel].omschr,
									Hoofdmenu->LL_vent_Tabel[tel].bestelnr,
									Hoofdmenu->LL_vent_Tabel[tel].Paanspr,
									Hoofdmenu->LL_vent_Tabel[tel].Pnood,
									Hoofdmenu->LL_vent_Tabel[tel].P1_fact,
									Hoofdmenu->LL_vent_Tabel[tel].P4_fact,
									Hoofdmenu->LL_vent_Tabel[tel].Pinspr);
			}
			fclose (stream);
		}
		else Boodschap ("Fout in openen van bestand LL_VENT.DAT !");
	}
}

// ======================== opslaan veerkar tabel ===============================
void Opslaan_VE(Menus *Hoofdmenu)
{	int tel, tel2, controle=0;
	FILE *stream = NULL;

	remove("veerkar.bak");
	if (rename("veerkar.dat", "veerkar.bak") == 0) controle=1;
	else Boodschap("Fout in creeren backup file VEERKAR.BAK of .DAT file niet gevonden!");

	if (controle)
	{	if ((stream = fopen("veerkar.dat", "wt")) != NULL)
		{	fseek(stream, 0, SEEK_SET);
			for (tel=0; tel < 25; tel++)
			{	fprintf (stream, "|%4d |%-30s|%-20s|",
									Hoofdmenu->Veerkar_Tabel[tel].nummer,
									Hoofdmenu->Veerkar_Tabel[tel].omschr,
									Hoofdmenu->Veerkar_Tabel[tel].bestelnr);
				for (tel2=0; tel2<10; tel2++)
				{	fprintf (stream, "%7.1f |%7.1f |",
									Hoofdmenu->Veerkar_Tabel[tel].waarden[tel2][0],
									Hoofdmenu->Veerkar_Tabel[tel].waarden[tel2][1]);
				}
				fprintf (stream, "\n");
			}
			fclose (stream);
		}
		else Boodschap ("Fout in openen van bestand VEERKAR.DAT !");
	}
}

// ============== functie voor het afbeelden van de voertuigbestanden =====
void Afbeeld_Voert (void)
{	char kar = 32, inleesregel [60], nummer[60] = "", naam[60] = "";
	FILE *stream;
	struct find_t Gegevens;
	int done, tel;

	clrscr();
	textcolor(LIGHTGREEN);
	cprintf ("Overzicht voertuigbestanden\n\n\r");
	textcolor (WHITE);
	cprintf("Filenaam      Nummer  Voertuigtype");
	textcolor(LIGHTGRAY);
	window (1,4,80,25);
	gotoxy (1,1);
	tel=0;

	done = _dos_findfirst("vt*.dat",_A_NORMAL, &Gegevens);
	while (!(done) && kar != 27)
	{	if ((stream = fopen(Gegevens.name, "rt")) != 0)
		{	/* seek to the start of the file */
			fseek(stream, 0, SEEK_SET);

			// Eerste twee regels lezen uit file
			if(fgets(inleesregel, 50, stream)) strcpy (nummer, inleesregel);
			if(fgets(inleesregel, 50, stream)) strcpy (naam, inleesregel);

			// "\n" weghalen aan einde string
			nummer[strlen(nummer)-1] = '\0';
			fclose (stream);
		}
		cprintf("%-12s %6s    %s\r", Gegevens.name, nummer, naam);
		done = _dos_findnext(&Gegevens);

		if (tel>0 && (tel+1)%20==0)
		{  textcolor(WHITE);
			cprintf ("Bedien een toets voor vervolg  Esc = einde");
			textcolor (LIGHTGRAY);
			kar = getch();
			clrscr();
		}
		tel++;
	}
	if (kar != 27)
	{  textcolor(WHITE);
		cprintf ("Bedien een toets....");
		textcolor (LIGHTGRAY);
		kar = getch();
	}
	window (1,1,80,25);
//	clrscr();
}