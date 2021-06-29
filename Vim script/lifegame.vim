" Vim plugin for Conway's life game

if exists("g:loaded_lifegame")
	"finish
endif
let g:loaded_lifegame = 1

let s:save_cpo = &cpo
set cpo&vim


"function s:readState(start, end)
function s:readState()
	"let l:line = getline(start, end)
	let l:line = getline(1, line('$'))
	echo l:line
endfunction











if !exists(":Lifegame")
	command -nargs=0 Lifegame :call <SID>readState()
endif

let &cpo = s:save_cpo
unlet s:save_cpo

