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
(0, 1, 1, 1), (1, 2, 1, 1),
(0, 2, 1, 1), (2, 3, 1, 1),
(2, 4, 1, 1), (3, 4, 1, 1),
(0, 8, 1, 1), (8, 9, 1, 1), 
(9, 10, 1, 1), (10, 8, 1, 1);

SELECT * FROM pgr_bridges (
	'SELECT id, source, target, cost, reverse_cost FROM edge_table');

/*************OUTPUT******************
 seq | edge 
-----+------
   1 |    7
(1 rows)
*************************************/

