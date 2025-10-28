# Git: как мы работаем

Минимум теории, максимум практики. Базовая ветка — `develop`. У каждого разработчика своя ветка. По согласию можно подтягивать изменения из других веток. По завершении работы — влить свою ветку в `develop` (через PR).

## Содержание
- 1) Разовая настройка
- 2) Клонирование репозитория
- 3) Ежедневный поток работы
- 4) Правила команды
- 5) Конфликты — короткий рецепт
- 6) Шпаргалка
- 7) Проблемы и решения

## 1) Разовая настройка
```bash
git config --global user.name "Ваше Имя"
git config --global user.email "you@example.com"
git config --global core.autocrlf true     # Windows переводы строк
```
Опционально SSH:
```bash
ssh-keygen -t ed25519 -C "you@example.com"
# Добавьте публичный ключ в GitHub → Settings → SSH and GPG keys
ssh -T git@github.com   # проверка
```

## 2) Клонирование репозитория

SSH (после настройки ключа):
```bash
git clone git@github.com:<owner>/<repo>.git
cd <repo>
git remote -v
```

HTTPS (если SSH пока не готов):
```bash
git clone https://github.com/<owner>/<repo>.git
cd <repo>
git remote -v
```

Подсказка: для проверки SSH используйте именно `ssh -T git@github.com` (а не `user@github.com`).
Примечание: при успешной проверке GitHub пишет сообщение вида
"Hi <user>! You've successfully authenticated, but GitHub does not provide shell access." — это нормально, код выхода может быть 1.

## 3) Ежедневный поток работы

1. Обновить `develop` и создать свою ветку
```bash
git fetch origin
git switch develop
git pull --ff-only
git switch -c user/<имя>   # или feature/<задача>
```

2. Работать и коммитить небольшими порциями
```bash
git status
git add <файлы>
git commit -m "feat: кратко что сделано"
```

3. Периодически подтягивать свежий `develop`
```bash
git fetch origin
git merge origin/develop   # допустимо rebase, если привычно
```

4. При необходимости взять изменения из другой ветки (по согласию автора)
```bash
git fetch origin
git merge origin/user/<другой>   # или origin/feature/<задача>
```

5. Опубликовать ветку и открыть PR → `develop`
```bash
git push -u origin user/<имя>
# создайте Pull Request: user/<имя> → develop
```

6. Завершение: влить PR, удалить ветку (по желанию)

## 4) Правила команды
- Небольшие, понятные коммиты; осмысленные сообщения.
- Одна задача — одна ветка; не мешайте разные задачи.
- Перед PR обновите ветку от `develop` и убедитесь, что проект собирается.
- Не коммитьте бинарники и секреты.

## 5) Конфликты — короткий рецепт
```bash
git fetch origin
git merge origin/develop
# исправьте конфликты в файлах
git add <исправленные_файлы>
git commit
```
Если всё сложно — спросите в чате, не усугубляйте историю.

## 6) Шпаргалка
```bash
git status                                   # что изменилось
git log --oneline --graph -n 20              # короткий журнал
git branch -vv                               # ветки лок/удалённые
git switch <ветка> | git switch -c <новая>   # переход/создание ветки
git fetch --all --prune                      # подтянуть всё и очистить
git push | git pull --ff-only                # публикация/обновление
git commit --amend                           # поправить последний коммит
```

## 7) Проблемы и решения
- Permission denied (publickey): настройте SSH-ключ и добавьте в GitHub.
- Конфликты: следуйте рецепту из раздела 4.
- Если возникают какие то еще проблемы смело пиши в чат

— Конец —
