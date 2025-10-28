# clang-format (Windows и Linux)

Этот документ — короткая, но полная инструкция по установке, настройке и использованию clang-format для C/C++.

Конфигурация проекта (пример .clang-format):

```yaml
---
BasedOnStyle: Google
IndentWidth: 4
ColumnLimit: 110
```

Что это значит:
- Базовый стиль: Google, но с отступами 4 пробела.
- Максимальная длина строки: 110 символов.

Важно: положите файл `.clang-format` в корень репозитория, чтобы форматтер всегда его находил.

---

## 1) Установка

Windows (PowerShell):

```powershell
# Проверить, установлен ли пакетный менеджер Chocolatey
choco --version

# Установить clang-format (в составе LLVM)
choco install llvm -y

# Альтернатива: Scoop (если он установлен)
scoop install llvm
```

Linux (Debian/Ubuntu):

```bash
sudo apt update
sudo apt install -y clang-format
```

Проверка установки (обе ОС):

```powershell
# Windows PowerShell
clang-format --version
```
```bash
# Linux
clang-format --version
```

---

## 2) Базовое использование

Форматировать один файл:

```powershell
# Windows
clang-format -i src\main.cpp
```
```bash
# Linux
clang-format -i src/main.cpp
```

Форматировать все исходники в папке `src` рекурсивно:

```powershell
# Windows (PowerShell)
Get-ChildItem -Path src -Recurse -Include *.cpp,*.c,*.h,*.hpp | ForEach-Object { clang-format -i $_.FullName }
```
```bash
# Linux (bash)
find src -type f \( -name "*.cpp" -o -name "*.c" -o -name "*.h" -o -name "*.hpp" \) -print0 | xargs -0 clang-format -i
```

Форматировать только изменённые в git файлы:

```powershell
# Windows (изменённые относительно HEAD)
git diff --name-only HEAD -- '*.c' '*.cpp' '*.h' '*.hpp' | ForEach-Object { clang-format -i $_ }
```
```bash
# Linux (изменённые относительно HEAD)
git diff --name-only HEAD -- '*.c' '*.cpp' '*.h' '*.hpp' | xargs -r clang-format -i
```

---

## 3) Проверка без внесения изменений (dry-run)

Показать, будет ли переформатирование (не изменяя файлы):

```powershell
# Windows
clang-format -n -Werror -style=file src\main.cpp
```
```bash
# Linux
clang-format -n -Werror -style=file src/main.cpp
```

Проверить все файлы в `src` и завершиться ошибкой, если есть отличия:

```powershell
# Windows
$files = Get-ChildItem -Path src -Recurse -Include *.cpp,*.c,*.h,*.hpp | Select-Object -ExpandProperty FullName
foreach ($f in $files) { clang-format -n -Werror -style=file $f }
```
```bash
# Linux
find src -type f \( -name "*.cpp" -o -name "*.c" -o -name "*.h" -o -name "*.hpp" \) -print0 | xargs -0 -I {} clang-format -n -Werror -style=file {}
```

---

## 4) Диагностика

Убедиться, что используется ваш файл `.clang-format` и нужные параметры применяются:

```powershell
# Windows
clang-format -style=file -assume-filename=src\main.cpp -dump-config | Select-String "IndentWidth|BasedOnStyle|ColumnLimit"
```
```bash
# Linux
clang-format -style=file -assume-filename=src/main.cpp -dump-config | egrep "IndentWidth|BasedOnStyle|ColumnLimit"
```

Если `IndentWidth` не равен 4 или `BasedOnStyle` не Google:
- Проверьте, что `.clang-format` лежит в корне репозитория.
- Убедитесь, что форматирование запускается из каталога проекта (или передайте правильный путь через `-assume-filename`).

Проверить, что clang-format доступен из PATH:

```powershell
# Windows
Get-Command clang-format -ErrorAction SilentlyContinue
where.exe clang-format
```
```bash
# Linux
which clang-format
```

---

## 5) Рекомендуемый рабочий процесс

1. Перед коммитом форматируйте все изменённые C/C++ файлы (см. команды выше).
2. Держите `.clang-format` в корне репозитория и версионируйте его.
3. При код-ревью используйте dry-run проверки, чтобы убедиться в соответствии стилю.

