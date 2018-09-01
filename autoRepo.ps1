New-Alias -Name git -Value "$Env:ProgramFiles\Git\bin\git.exe"
git init
git status
git add .
git commit -m "initial commit"
git log