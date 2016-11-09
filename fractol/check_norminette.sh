#!/bin/bash

##/Users/tdefresn/.brew/Cellar/bash/4.4_1/bin/bash

#echo "This script requires at least bash 4.0"


#shopt -s extglob

#ls (*/)5/*[!mlx][!mlx_int][!mlx_new_window].[ch]
#ls ***/!(*mlx).[ch]

find -L . -type f \( -iname "*.[ch]" -a -not -iname "*mlx*" \) -exec norminette {} +
#	echo "a"
#	norminette "$line"
#done
