DROP TABLE IF EXISTS edge_table;
CREATE TABLE edge_table (
	id BIGSERIAL,
	source BIGINT,
	target BIGINT,
	cost FLOAT,
	reverse_cost FLOAT
);

INSERT INTO edge_table (
	source, target,
	cost, reverse_cost) VALUES
(0, 1, 1, -1), (1, 2, 1, -1),
(0, 2, 1, -1), (2, 4, 1, -1),
(1, 4, -1, 1), (3, 5, 1, -1),
(5, 6, 1, -1);

SELECT * FROM pgr_strongComponents (
	'SELECT id, source, target, cost, reverse_cost FROM edge_table');

/*************OUTPUT******************
 seq | component | n_seq | node 
-----+-----------+-------+------
   1 |         0 |     1 |    0
   2 |         1 |     1 |    1
   3 |         1 |     2 |    2
   4 |         1 |     3 |    4
   5 |         3 |     1 |    3
   6 |         5 |     1 |    5
   7 |         6 |     1 |    6
(7 rows)
*************************************/

