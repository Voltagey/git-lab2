CREATE TABLE firms (
    id INTEGER PRIMARY KEY NOT NULL,
    name VARCHAR(30),
    city VARCHAR(30),
    industry VARCHAR(30),
    employees INTEGER,
    revenue FLOAT,
    avg_salary FLOAT
);

INSERT INTO firms (id, name, city, industry, employees, revenue, avg_salary) VALUES
(1, 'Yandex', 'Moscow', 'IT', 25000, 800.5, 210.0),
(2, 'Gazprom', 'SPb', 'Energy', 490000, 8500.0, 165.0),
(3, 'Ozon', 'Moscow', 'Ecommerce', 60000, 420.2, 140.0),
(4, 'VK', 'Moscow', 'IT', 15000, 135.0, 185.0),
(5, 'Lukoil', 'Moscow', 'Energy', 110000, 7900.0, 175.0),
(6, 'Tinkoff', 'Moscow', 'Fintech', 45000, 510.8, 195.0),
(7, 'Sber', 'Moscow', 'Fintech', 280000, 4300.0, 180.0),
(8, 'Selectel', 'SPb', 'IT', 1200, 12.5, 190.0),
(9, 'Wildberries', 'Moscow', 'Ecommerce', 95000, 540.0, 135.0),
(10, 'Kaspersky', 'Moscow', 'IT', 5000, 75.4, 205.0);
