@echo off
chcp 65001 > nul

:: Переходим в корень проекта (на один уровень вверх относительно папки scripts)
cd /d "%~dp0.."

:: Создаем папку build, если её нет
if not exist build (
    mkdir build
)

:: Переходим в папку build
cd build

:: Запускаем генерацию проекта CMake (для Visual Studio)
echo Запуск CMake...
cmake -G "Visual Studio 18 2026" ..

:: 1. Сначала пробуем найти и открыть новый формат .slnx
for %%f in (*.slnx) do (
    if defined VS_PATH (
        echo Открываю современное решение %%f через Visual Studio...
        start "" "%VS_PATH%" "%%f"
    ) else (
        start "" "%%f"
    )
    goto :exit_script
)
    
cmake -G "Visual Studio 17 2022" ..
    
:: 2. Если .slnx нет, ищем классический .sln
for %%f in (*.sln) do (
    if defined VS_PATH (
        echo Открываю классическое решение %%f через Visual Studio...
        start "" "%VS_PATH%" "%%f"
    ) else (
        start "" "%%f"
    )
    goto :exit_script
)

:exit_script
