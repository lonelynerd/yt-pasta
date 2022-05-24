#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000
#define MAXSTR "1000"

int print_error(int type, const char err[]);
void clear_file(const char *filename);
void title(int ctrlc);

int main(void) {
	menu: system("cls");
	title(1);
	FILE *config = fopen("config.txt", "r+");
	if (config == NULL) {
		print_error(0,
		            "Le fichier de configuration n'existe pas ou est inaccessible.");
		system("pause");
		return EXIT_FAILURE;
	}
	char dldir[MAX];
	fread(dldir, sizeof(char), MAX, config);
	if (!feof(config)) {
		print_error(0, "Le fichier est illisible.");
		fclose(config);
		system("pause");
		return EXIT_FAILURE;
	}

	//dldir[strlen(dldir) - 2] = '\0'; //trim last char

	char flext[10];

	rewind(config);
	char entree = 'e';
	print_error(3,"Que voulez-vous faire ?");
	printf("\tA -> Telecharger un audio\n");
	printf("\tV -> Telecharger une video\n\n");
	printf("\tN -> Afficher le chemin du dossier de telechargement\n");
	printf("\tT -> Definir un dossier de telechargement\n");
	printf("\tD -> Acceder au dossier\n\n");
	printf("\tQ -> Quitter\n\n");

	printf(">>> ");
	if (scanf(" %c", &entree) != 1) {
		system("cls");
		title(0);
		print_error(0, "Entree invalide");
		system("pause");
		goto menu;
	}
	printf("\n");
	char param[MAX] = " ";
	switch (tolower(entree)) {
	case 'a':
		system("cls");
		title(0);
		strcat(param, "-x ");
		print_error(2,
		            "Pour que l'application fonctionne correctement, il est necessaire d'installer ffmpeg.");
		strcat(param, "--audio-format ");
		print_error(3,"Dans quel format voulez-vous que l'audio soit telecharge ?");
		printf("\t1 -> mp3\n");
		printf("\t2 -> wav\n");
		printf("\t3 -> flac\n\n");
		printf(">>> ");
		if (scanf(" %c", &entree) != 1) {
			printf("\n");
			print_error(0, "Entree invalide");
			system("pause");
			goto menu;
		}
		printf("\n");
		switch (tolower(entree)) {
		case '1':
			strcat(param, "mp3 ");
			strcat(flext,"*.mp3 ");
			break;
		case '2':
			strcat(param, "wav ");
			strcat(flext,"*.wav ");
			break;
		case '3':
			strcat(param, "flac ");
			strcat(flext,"*.flac ");
			break;
		default:
			system("cls");
			title(0);
			print_error(0, "Entree invalide");
			system("pause");
			goto menu;
			break;
		}
		break;
	case 'v':
		system("cls");
		title(0);
		strcat(param, "-f ");
		print_error(3,"Dans quel format voulez-vous que la video soit telecharge ?");
		printf("\t1 -> mp4\n");
		printf("\t2 -> webm\n");
		printf("\t3 -> ogg\n\n");
		printf(">>> ");
		if (scanf(" %c", &entree) != 1) {
			printf("\n");
			print_error(0, "Entree invalide");
			system("pause");
			goto menu;
		}
		switch (tolower(entree)) {
		case '1':
			strcat(param, "mp4 ");
			strcat(flext,"*.mp4 ");
			break;
		case '2':
			strcat(param, "webm ");
			strcat(flext,"*.webm ");
			break;
		case '3':
			strcat(param, "ogg ");
			strcat(flext,"*.ogg ");
			break;
		default:
			system("cls");
			title(0);
			print_error(0, "Entree invalide");
			system("pause");
			goto menu;
			break;
		}
		break;
	case 'n':
		system("cls");
		title(0);
		printf("[Remarque] Dossier defini actuellement : \"%s\"\n\n", dldir);
		system("pause");
		goto menu;
		break;
	case 't':
		system("cls");
		title(0);
		printf("[Remarque] Dossier defini actuellement : \"%s\"\n\n", dldir);
		print_error(2,"Vous devez faire attention au format ! Tout chemin errone peut occasioner un comportement invoulu.");
		print_error(3,
		        "Quel emplacement voulez-vous definir pour la sauvegarde des fichiers (sans \"\\\" a la fin ) ?\n");
		printf(">>> ");
		if (scanf(" %"MAXSTR "[^\n]", dldir) != 1) {
			system("cls");
			title(0);
			print_error(0, "Entree invalide");
			system("pause");
			goto menu;
		}
		clear_file("config.txt");
		//dldir[strlen(dldir)] = '\0';
		if (fwrite(dldir, sizeof(char), strlen(dldir)+1, config) == 0) {
			system("cls");
			title(0);
			print_error(0, "Le parametre n'a pas pu être edite.");
			fclose(config);
			system("pause");
			return EXIT_FAILURE;
		}
		system("cls");
		title(0);
		print_error(1, "Le parametre a ete edite correctement");
		printf("[Remarque] Emplacement choisi : %s\n", dldir);
		system("pause");
		goto menu;
		break;
	case 'd':
		system("cls");
		title(0);
		printf("[Remarque] Ouverture du dossier. \"%s\"\n\n", dldir);
		char dldir_final[MAX] = "explorer.exe ";
		strcat(dldir_final, dldir);
		if(system(dldir_final) != true){
			system("cls");
			title(0);
			print_error(0,"Le dossier n'existe pas.");
			system("pause");
			goto menu;
		}
		print_error(1, "Fini.");
		system("pause");
		goto menu;
		break;
	case 'q':
		system("cls");
		title(0);
		print_error(1, "Arret.");
		if(fclose(config) != 0){
			print_error(0, "Le fichier n'a pas pu être fermé correctement.");
			system("pause");
			return EXIT_FAILURE;
		}
		system("pause");
		return EXIT_SUCCESS;
		break;
	default:
		system("cls");
		title(0);
		print_error(0, "Entree invalide.");
		system("pause");
		goto menu;
		break;
	}
	system("cls");
	title(0);
	char url[MAX];
	print_error(3,"Entrez les liens YouTube separes par des espaces:\n");
	printf(">>> ");
	if (scanf(" %"MAXSTR "[^\n]", url) != 1) {
		system("cls");
		title(0);
		printf("Erreur : lien invalide. ");
		system("pause");
		goto menu;
	}
	system("cls");
	title(0);
	char final[MAX] = ".\\youtube-dl";
	strcat(final, param);
	strcat(final, url);
	//char title[MAX] = ".\\youtube-dl -e ";
	//strcat(title, url);
	//printf("\nTitre : ");
	//if (system(title) != 0) {
	//  printf("\n");
	//  print_error(0,
	//      "Le logiciel a encontre une erreur. Veuillez recommencer.");
	//  system("pause");
	//  return EXIT_FAILURE;
	//}
	printf("[Remarque] Commande : %s\n", final);
	char godir[MAX] = "move ";
	strcat(godir,flext);
	//strcat(godir," ");
	strcat(godir,dldir);
	printf("[Remarque] Commande de deplacement : %s\n\n",godir);
	if (system(final) != 0) {
		system("cls");
		title(0);
		print_error(0,
		            "Le logiciel a encontre une erreur. Veuillez recommencer.");
		system("pause");
		goto menu;
	} else {
		system("cls");
		title(0);
		if(system(godir) != 0){
			system("cls");
			title(0);
			print_error(0,"Le dossier n'existe pas, le deplacement n'a pas ete effectuee...");
		}
		printf("[Remarque] Ouverture du dossier. \"%s\"\n", dldir);
		char dldir_final[MAX] = "explorer.exe ";
		strcat(dldir_final, dldir);
		if(system(dldir_final) != true){
			system("cls");
			title(0);
			print_error(0,"Le dossier n'existe pas, ouverture du dossier de l'application...");
			system("explorer.exe .");
		}
		print_error(1,"Fait. ");
		system("pause");
	}
	if(fclose(config) != 0){
		print_error(0, "Le fichier n'a pas pu être fermé correctement.");
		system("pause");
		return EXIT_FAILURE;
	}
	goto menu;
}

int print_error(int type, const char err[]) {
	switch (type) {
	case 0:
		fprintf(stderr, "[Erreur] ");
		break;
	case 1:
		fprintf(stdout, "[Remarque] ");
		break;
	case 2:
		fprintf(stdout, "[Attention] ");
		break;
	case 3:
		fprintf(stdout, "[Question] ");
		break;
	default:
		return -1;
		break;
	}
	printf("%s\n\n", err);
	//if( type == 3 ){
	//	printf("\n");
	//}
	return 0;
}

void clear_file(const char *filename){
	FILE *output = fopen(filename, "w");
	fclose(output);
}

void title(int ctrlc){
	system("cls");
	printf("                                                                             \n _|      _|  _|_|_|_|_|  _|_|_|      _|_|      _|_|_|  _|_|_|_|_|    _|_|    \n   _|  _|        _|      _|    _|  _|    _|  _|            _|      _|    _|  \n     _|          _|      _|_|_|    _|_|_|_|    _|_|        _|      _|_|_|_|  \n     _|          _|      _|        _|    _|        _|      _|      _|    _|  \n     _|          _|      _|        _|    _|  _|_|_|        _|      _|    _|  \n\n\n");
	printf(
	        "Version : 0.1.1 Stable\nAuteur : Theo SALLES (Nerd)\nE-mail : imalonelynerd@gmail.com\nLicense : WTFPL (http://www.wtfpl.net/txt/copying/)\nLogo : Icons8 (https://icons8.com/icon/9a46bTk3awwI/youtube)");
	if(ctrlc == 1){
		printf("\n\n");
		printf("En cas de fausse manipulation, ou pour interrompre le programme, veuillez taper Ctrl + C.");
		printf("\n\n\n");
	}else{
		printf("\n\n\n");
	}
}
