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
 seq | node_seq | node | component 
-----+----------+------+-----------
   1 |        1 |    0 |         1 
   2 |        2 |    1 |         1 
   3 |        3 |    4 |         1 
   4 |        1 |    2 |         2 
   5 |        2 |    5 |         2 
   6 |        1 |    3 |         3 
(6 rows)
*************************************/

