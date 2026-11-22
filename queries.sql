-- База данных (SELECT *)
SELECT * FROM firms;

-- Задание 1. Просмотр содержимого выбранных полей
SELECT name, city, industry, revenue FROM firms;

-- Задание 2. Сортировка по возрастанию и убыванию
SELECT name, revenue FROM firms ORDER BY revenue DESC;

-- Задание 3. Условие отбора (одно условие: отрасль IT)
SELECT name, city, employees, avg_salary FROM firms WHERE industry = 'IT';

-- Задание 4. Два условия отбора (город Moscow и зарплата >= 190)
SELECT name, industry, avg_salary FROM firms WHERE city = 'Moscow' AND avg_salary >= 190;

-- Задание 5. Добавление записи, обновление (повторяющиеся значения) и агрегация
INSERT INTO firms VALUES (11, 'JetBrains', 'SPb', 'IT', 2000, 300.0, 230.0);
UPDATE firms SET city = 'SPb' WHERE name = 'VK';
SELECT COUNT(DISTINCT city) AS unique_cities FROM firms;
SELECT city, COUNT(*) AS firm_count FROM firms GROUP BY city;
SELECT COUNT(*) AS total_firms, SUM(employees) AS total_staff, AVG(avg_salary) AS mean_salary FROM firms;

-- Задание 6. Подсчет записей до и после удаления одной записи
SELECT COUNT(*) FROM firms;
DELETE FROM firms WHERE id = 11;
SELECT COUNT(*) FROM firms;
