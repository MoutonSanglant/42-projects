PROJECTS = fillit push_swap lem_in ls minishell 42sh fdf fractol

.PHONY: $(PROJECTS)

all:

$(PROJECTS):
	@echo "=== $@ ==="
	@$(MAKE) -C $@ correction_$@
	@cp ./auteur /tmp/$@

libft:
	@echo "libft not implemented yet"

libftprintf:
	@echo "libftprintf not implemented yet"
