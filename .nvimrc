" Config
set tabstop=2
set shiftwidth=2

" vim-cmake configuration
let s:bin_folder = "bin"
let s:runner = "pmr"
let s:args = ""

let g:cmake_build_dir_location = "build"
let g:cmake_link_compile_commands = 1
let g:cmake_generate_options = []
let g:cmake_build_options = ["--target", s:runner, "--", "-j10"]

" Key bindings
map <F7>  :CMakeGenerate<CR>
map <C-b> :CMakeBuild<CR>
map <C-x> :CMakeClean<CR>
map <F5>  :Run<CR>
map <C-r> :BuildRun<CR>

" Go to bin directory
function! GoToBinDir()
    return ['cd', s:bin_folder]
endfunction

" Launch runner
function! LaunchRunner()
    return ['./' . s:runner, s:args]
endfunction

" Execute Run command in a vim-cmake console
function! ExecuteRun()
  let l:command = ['(']
  let l:command += GoToBinDir()
  let l:command += ['&&']
  let l:command += LaunchRunner()
  let l:command += [')']
  call cmake#console#SetCmdId('run')
  call cmake#command#Run(l:command, 0, 0)
endfunction

" Run
function! Run()
    call ExecuteRun()
endfunction

command! Run call Run()

" Build & Run
function! BuildRun()
    execute 'CMakeBuild'
    call Run()
endfunction

command! BuildRun call BuildRun()

