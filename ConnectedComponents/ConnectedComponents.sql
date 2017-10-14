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
(0, 1, 1, 1), (1, 4, 1, 1),
(0, 4, 1, 1), (2, 5, 1, 1),
(3, 3, 1, 1);

SELECT * FROM pgr_connectedComponents (
	'SELECT id, source, target, cost, reverse_cost FROM edge_table');

/*************OUTPUT******************
 seq | component | n_seq | node 
-----+-----------+-------+------
   1 |         0 |     1 |    0
   2 |         0 |     2 |    1
   3 |         0 |     3 |    4
   4 |         2 |     1 |    2
   5 |         2 |     2 |    5
   6 |         3 |     1 |    3
(6 rows)
*************************************/

