#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <math.h>
#include "EL_Convertor_2000.h"
#include <Windows.h>


int main(int argc, char* argv[])//args
{
	SetConsoleOutputCP(CP_UTF8);

	std::vector<std::string> palette;
	std::string file_name;
	std::string new_file;

	bool input_is_true=0, output_is_true=0, palette_is_true=0;

	if (argc > 1)
	{
		if (strcmp(argv[1], "--help") == 0)
		{
			std::cout << "Usage :\npgm2txt [options]\n\nOptions :\n";
			std::cout << "--input fichier\t\tSpécifie le fichier image à convertir Si ce paramètre n'est pas spécifié, le fichier est demandé via la console.\n\n";
			std::cout << "--output fichier\t\tSpécifie le nom du fichier texte qui contiendra l'Ascii Art. Si ce paramètre n'est pas spécifié, l'Ascii Art est sortie dans la console.\n\n";
			std::cout << "--palette fichier\t\tSpécifie un fichier texte contenant la palette de couleur Ascii. Chaque ligne du fichier contient un charactère en UTF - 8, du plus sombre au plus clair. Si ce paramètre n'est pas spécifié, la palette par défaut est \"W\", \"w", "l", "i", ":\", \",\", \".\", \" \" \n\n";
			std::cout << "--help\t\t\tAffiche cette aide.\n\n";
			std::cout << "--width nombre\t\tSpécifie la largeur max de l'Ascii Art. Si ce paramètre n'est pas spécifié, aucune limite n'est fixée. Voir Remarques.\n\n";
			std::cout << "--height nombr\t\tSpécifie la hauteur max de l'Ascii Art. Si ce paramètre n'est pas spécifié, aucune limite n'est fixée. Voir Remarques.\n\n";
			std::cout << "Remarques :\nQuelles que soient les valeurs des options --width et --height, la taille de l'Ascii Art est bornée par la taille de l'image en entrée. La taille de l'ascii art conserve toujours le même ratio que l'image d'entrée, les valeurs des options --width et --height ne sont que des maximums.";
			return 0;
		}
		else
		{
			for (int i = 1; i < argc; i += 2)
			{
				if (strcmp(argv[i], "--input") == 0 && !input_is_true)
				{
					file_name = argv[i + 1];
					input_is_true = 1;
				}

				if (strcmp(argv[i], "--output") == 0 && !output_is_true)
				{
					new_file = argv[i + 1];
					output_is_true = 1;

				}
				if (strcmp(argv[i], "--palette") == 0 && !palette_is_true)
				{
					palette = dec_pal(argv[i + 1]);
					palette_is_true = 1;
				}
			}
		}
	}
	

	if (!input_is_true)
	{
		file_name = GetNomFichier();
	}
	if (!palette_is_true)
	{
		palette = { "W", "w", "l", "i", ":", ",", ".", " " };
	}
	if (!output_is_true)
	{
		std::vector<std::vector<int>> Tab = fileToTab(file_name,100,100);
		diplayConsole(Tab, palette);
	}
	if (output_is_true)
	{
		std::vector<std::vector<int>> tab = fileToTab(file_name, 100, 100);
		new_file = "../" + new_file + ".txt";
		createFile(tab , new_file, palette);
		createFile(reechantillionnage(tab, 10, 200),"../tagrandmereleplatipus",palette);
	}
}


