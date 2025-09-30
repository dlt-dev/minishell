
// int determine_mode(char *str)
// { 
// 	int i;
	 
// 	i = 0;
// 	while(is_separator(str[i]) == IS_NOT && str[i] != '\0')
// 	{ 
// 		if(str[i] == "\"" || str[i] == "\'")
// 			return(MODE_QUOTES);
// 		i++;
// 	}
// 	return(MODE_GEN);
// }

/**
 * @brief 
 * 
 * espace = " \t\n\v\f\r" // si c'est autre chose qu'espace on arrete
	quote = " \"\'" // si on touche au deuxieme quote on s'arrete
	pipe = "|<>\t\n\v\f\r" // on regarde le caractere suivant et on s'arrete  toutde
	// suite si autre chose qu'un pipe et   
	dollars = "\t\n\v\"
	different = " \t\n\v\f\r\'\'|<>$"
 * 
 */