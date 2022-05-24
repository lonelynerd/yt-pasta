#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000
#define MAXSTR "1000"

int print_error(int type, const char err[]);
void clear_file(const char *filename);
void title(void);

int main(void) {

	//affichage menu de base

	system("cls");
	title();

	//ouverture de fichier + erreur

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
	printf("Que voulez-vous faire ?\n\n");
	printf("\tA -> Telecharger un audio\n");
	printf("\tV -> Telecharger une video\n\n");
	printf("\tT -> Definir un dossier de telechargement\n");
	printf("\tD -> Acceder au dossier\n\n");
	printf("\tQ -> Quitter\n\n");

	printf(">>> ");
	if (scanf("%c", &entree) != 1) {
		system("cls");
		title();
		print_error(0, "Entree invalide");
		system("pause");
		return EXIT_FAILURE;
	}
	printf("\n");
	char param[MAX] = " ";
	switch (tolower(entree)) {
	case 'a':
		system("cls");
		title();
		strcat(param, "-x ");
		print_error(1,
		            "Pour que l'application fonctionne correctement, il est necessaire d'installer ffmpeg.");
		strcat(param, "--audio-format ");
		printf("\nDans quel format voulez-vous que l'audio soit telecharge ?\n\n");
		printf("\t1 -> mp3\n");
		printf("\t2 -> wav\n");
		printf("\t3 -> flac\n\n");
		printf(">>> ");
		if (scanf(" %c", &entree) != 1) {
			printf("\n");
			print_error(0, "Entree invalide");
			system("pause");
			return EXIT_FAILURE;
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
			title();
			print_error(0, "Entree invalide");
			system("pause");
			return EXIT_FAILURE;
			break;
		}
		break;
	case 'v':
		system("cls");
		title();
		strcat(param, "-f ");
		printf("Dans quel format voulez-vous que la video soit telecharge ?\n\n");
		printf("\t1 -> mp4\n");
		printf("\t2 -> webm\n");
		printf("\t3 -> ogg\n\n");
		printf(">>> ");
		if (scanf(" %c", &entree) != 1) {
			printf("\n");
			print_error(0, "Entree invalide");
			system("pause");
			return EXIT_FAILURE;
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
			title();
			print_error(0, "Entree invalide");
			system("pause");
			return EXIT_FAILURE;
			break;
		}
		break;
	case 't':
		system("cls");
		title();
		printf("[Remarque] Dossier defini actuellement : \"%s\"\n\n", dldir);
		printf(
		        "\nQuel emplacement voulez-vous definir pour la sauvegarde des fichiers (sans \"\\\" a la fin ) ?\n\n");
		printf(">>> ");
		if (scanf(" %"MAXSTR "[^\n]", dldir) != 1) {
			system("cls");
			title();
			print_error(0, "Entree invalide");
			system("pause");
			return EXIT_FAILURE;
		}
		clear_file("config.txt");
		//dldir[strlen(dldir)] = '\0';
		if (fwrite(dldir, sizeof(char), strlen(dldir)+1, config) == 0) {
			system("cls");
			title();
			print_error(0, "Le parametre n'a pas pu être edite.");
			fclose(config);
			return EXIT_FAILURE;
		}
		system("cls");
		title();
		print_error(1, "Le parametre a ete edite correctement");
		printf("Emplacement choisi : %s\n", dldir);
		system("pause");
		return EXIT_SUCCESS;
		break;
	case 'd':
		system("cls");
		title();
		printf("[Remarque] Ouverture du dossier. \"%s\"\n\n", dldir);
		char dldir_final[MAX] = "%windir%\\explorer.exe ";
		strcat(dldir_final, dldir);
		system(dldir_final);
		print_error(1, "Fini.");
		system("pause");
		return EXIT_SUCCESS;
		break;
	case 'q':
		system("cls");
		title();
		print_error(1, "Arret.");
		system("pause");
		return EXIT_SUCCESS;
		break;
	default:
		system("cls");
		title();
		print_error(0, "Entree invalide.");
		system("pause");
		return EXIT_SUCCESS;
		break;
	}
	system("cls");
	title();
	char url[MAX];
	printf("Entrez les liens YouTube separes par des espaces:\n\n");
	printf(">>> ");
	if (scanf(" %"MAXSTR "[^\n]", url) != 1) {
		system("cls");
		title();
		printf("Erreur : lien invalide. ");
		system("pause");
		return EXIT_FAILURE;
	}
	system("cls");
	title();
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
	printf("Commande : %s\n", final);
	char godir[MAX] = "move ";
	strcat(godir,flext);
	strcat(godir," ");
	strcat(godir,dldir);
	printf("[Remarque] Dossier de destination : %s\n\n",godir);
	if (system(final) != 0) {
		system("cls");
		title();
		print_error(0,
		            "Le logiciel a encontre une erreur. Veuillez recommencer.");
		system("pause");
		return EXIT_FAILURE;
	} else {
		system("cls");
		title();
		system(godir);
		printf("[Remarque] Ouverture du dossier. \"%s\"\n\n", dldir);
		char dldir_final[MAX] = "%windir%\\explorer.exe ";
		strcat(dldir_final, dldir);
		system(dldir_final);
		print_error(1,"Fait. ");
		system("pause");
	}
	return EXIT_SUCCESS;
}

int print_error(int type, const char err[]) {
	switch (type) {
	case 0:
		fprintf(stderr, "[Erreur] ");
		break;
	case 1:
		fprintf(stdout, "[Remarque] ");
		break;
	default:
		return -1;
		break;
	}
	printf("%s\n\n", err);
	return 0;
}

void clear_file(const char *filename){
	FILE *output = fopen(filename, "w");
	fclose(output);
}

void title(void){
	system("cls");
	printf("                                                                             \n _|      _|  _|_|_|_|_|  _|_|_|      _|_|      _|_|_|  _|_|_|_|_|    _|_|    \n   _|  _|        _|      _|    _|  _|    _|  _|            _|      _|    _|  \n     _|          _|      _|_|_|    _|_|_|_|    _|_|        _|      _|_|_|_|  \n     _|          _|      _|        _|    _|        _|      _|      _|    _|  \n     _|          _|      _|        _|    _|  _|_|_|        _|      _|    _|  \n\n\n");
	printf(
	        "Version : 0.1.0 Stable\nAuteur : Theo SALLES (Nerd)\nE-mail : imalonelynerd@gmail.com\nLicense : WTFPL (http://www.wtfpl.net/txt/copying/)\nLogo : Icons8 (https://icons8.com/icon/9a46bTk3awwI/youtube)");
	printf("\n\n\n");
}
