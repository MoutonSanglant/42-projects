#!/bin/bash

find -L . -type f \( -iname "*.[ch]" -a -not -iname "*mlx*" \) -exec norminette {} +
