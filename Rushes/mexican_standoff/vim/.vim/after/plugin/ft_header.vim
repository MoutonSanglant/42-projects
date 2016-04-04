" Remove stdHeader.vim autocmd Buffer write
autocmd! BufWritePre *
autocmd BufWritePre * call g:ListenBufWrite()

function g:ListenBufWrite()
	if exists ('&modified') && &modified
		call s:update()
	endif
endfunction

function s:update()

	if expand('%:e') == 'c'
		let l:pattern = s:start . repeat(' ', 5 - strlen(s:start)) . "Updated: [0-9]"
		let l:line = getline (9)
		if l:line =~ l:pattern
			call setline(9, s:updateline())
		endif
	endif
endfunction

command AppendHeader call s:insert()
nmap <C-C>h :AppendHeader<CR>


let s:asciiart = [
			\"        :::      ::::::::",
			\"      :+:      :+:    :+:",
			\"    +:+ +:+         +:+  ",
			\"  +#+  +:+       +#+     ",
			\"+#+#+#+#+#+   +#+        ",
			\"     #+#    #+#          ",
			\"    ###   ########.fr    "
			\]

let s:linelen		= 80
let s:marginlen		= 5
let s:contentlen	= s:linelen - (3 * s:marginlen - 1) - strlen(s:asciiart[0])

let s:star = '*'
let s:end = '*/'
let s:start = '/*'


function s:insert()
	if s:checkHeader() == -1
		call append (0, "")
		call append (0, s:starline())
		call append (0, s:emptyline())
		call append (0, s:updateline())
		call append (0, s:createline())
		call append (0, s:logo3())
		call append (0, s:coderline())
		call append (0, s:logo2())
		call append (0, s:fileline())
		call append (0, s:logo1())
		call append (0, s:emptyline())
		call append (0, s:starline())
	endif
endfunction

function s:checkHeader()
	let l:counter = 1
	let l:lines = ""
	while l:counter <= 11
		let l:lines = l:lines . getline(l:counter) . "\n"
		let l:counter += 1
	endwhile
	let	l:pattern = s:starline() . "\n"
	let	l:pattern = l:pattern . s:emptyline() . "\n"
	let	l:pattern = l:pattern . s:logo1() . "\n"
	let	l:pattern = l:pattern . s:fileline() . "\n"
	let	l:pattern = l:pattern . s:logo2() . "\\n"
	let	l:pattern = l:pattern . s:coderline() . "\n"
	let	l:pattern = l:pattern . s:logo3() . "\n"
	let	l:pattern = l:pattern . s:createline() . "\n"
	let	l:pattern = l:pattern . s:updateline() . "\n"
	let	l:pattern = l:pattern . s:emptyline() . "\n"
	let	l:pattern = l:pattern . s:starline() . "\n"
"	let	l:pattern = substitute(l:pattern, '.', '\\.', 'g')
	let	l:pattern = substitute(l:pattern, '+', '\+', 'g')
	let	l:pattern = substitute(l:pattern, '*', '\\*', 'g')
	let	l:pattern = substitute(l:pattern, '/', '\/', 'g')
	let	l:pattern = substitute(l:pattern, '[0-9]', '[0-9]', 'g')
	let	l:test = match(l:lines, l:pattern)
	return l:test
endfunction

function s:escapedstarline ()
	return s:start . ' ' . repeat(('\' + s:star), s:linelen - 2 - strlen(s:start) - strlen(s:end)) . ' ' . s:end
endfunction

function s:starline ()
	return s:start . ' ' . repeat(s:star, s:linelen - 2 - strlen(s:start) - strlen(s:end)) . ' ' . s:end
endfunction

function s:emptyline ()
	return s:start . repeat(' ', s:linelen - strlen(s:start) - strlen(s:end)) . s:end
endfunction

function s:logo1 ()
	return s:left() . s:empty_content() . s:midgap() . s:asciiart[0] . s:right()
endfunction

function s:logo2 ()
	return s:left() . s:empty_content() . s:midgap() .s:asciiart[2] . s:right()
endfunction

function s:logo3 ()
	return s:left() . s:empty_content() . s:midgap() .s:asciiart[4] . s:right()
endfunction

function s:fileline ()
	let l:trimfile = strpart(fnamemodify(bufname('%'), ':t'), 0, s:contentlen)
	return s:left() . l:trimfile . repeat(' ', s:contentlen - strlen(l:trimfile)) . s:midgap() . s:asciiart[1] . s:right()
endfunction

function s:coderline ()
	let l:contentline = "By: ". s:trimlogin () . ' <' . s:trimemail () . '>'
	return s:left() . l:contentline . repeat(' ', s:contentlen - strlen(l:contentline)) . s:midgap() . s:asciiart[3] . s:right()
endfunction

function s:dateline (prefix, logo)
	let l:date = strftime("%Y/%m/%d %H:%M:%S")
	let l:contentline = a:prefix . ": " . l:date . " by " . s:trimlogin ()
	return s:left() . l:contentline . repeat(' ', s:contentlen - strlen(l:contentline)) . s:midgap() . s:asciiart[a:logo] . s:right()
endfunction

function s:createline ()
	return s:dateline("Created", 5)
endfunction

function s:updateline ()
	return s:dateline("Updated", 6)
endfunction


function s:left ()
	return s:start . s:lmargin()
endfunction

function s:right ()
	return s:rmargin() . s:end
endfunction

function s:lmargin ()
	return repeat(' ', s:marginlen - strlen(s:start))
endfunction

function s:rmargin ()
	return repeat(' ', s:marginlen - strlen(s:end))
endfunction

function s:empty_content ()
	return repeat(' ', s:contentlen)
endfunction

function s:midgap ()
	return repeat(' ', s:marginlen - 1)
endfunction

function s:trimlogin ()
	let l:trimlogin = strpart($USER, 0, 9)
	if strlen(l:trimlogin) == 0
		let l:trimlogin = "marvin"
	endif
	return l:trimlogin
endfunction

function s:trimemail ()
	let l:trimemail = strpart($MAIL, 0, s:contentlen - 16)
	if strlen(l:trimemail) == 0
		let l:trimemail = "marvin@42.fr"
	endif
	return l:trimemail
endfunction

