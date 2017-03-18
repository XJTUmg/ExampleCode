DROP TABLE IF EXISTS edge_table;
CREATE TABLE edge_table (
	id BIGSERIAL,
	source BIGINT,
	target BIGINT
);

INSERT INTO edge_table (
	source,
	target) VALUES
(0, 1), (1, 4),
(0, 4), (2, 5),
(3, 3);

SELECT * FROM pgr_connectedComponents (
	'SELECT id, source, target FROM edge_table');

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

