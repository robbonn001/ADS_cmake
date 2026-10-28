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
cmake -G "Visual Studio 17 2022" ..

:: Проверяем, успешно ли отработал CMake
if %errorlevel% equ 0 (
    echo.
    echo [УСПЕХ] Проект успешно сгенерирован! Ищу файл решения...
    
    :: Флаг, нашли ли мы файл
    set "found="
    
    :: Ищем файл .sln в текущей папке (build)
    for %%f in (*.sln) do (
        set "found=1"
        echo Найдено решение: %%f
        echo Открываю...
        :: Используем Проводник для гарантированного открытия файла по умолчанию
        explorer.exe "%%f"
        goto :exit_script
    )
    
    if not defined found (
        echo [ОШИБКА] Файл .sln не найден в папке build!
        echo Содержимое папки build:
        dir /b *.sln 2>nul || echo (Файлы .sln отсутствуют)
        pause
    )
) else (
    echo.
    echo [ОШИБКА] Ошибка при генерации проекта CMake. Решение не будет открыто.
    pause
)

:exit_script
