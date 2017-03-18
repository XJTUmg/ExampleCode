DROP TABLE IF EXISTS edge_table;
CREATE TABLE edge_table (
	id BIGSERIAL,
	source BIGINT,
	target BIGINT
);

INSERT INTO edge_table (
	source,
	target) VALUES
(0, 1), (1, 2),
(0, 2), (2, 4),
(4, 1), (3, 5),
(5, 6);

SELECT * FROM pgr_strongComponents (
	'SELECT id, source, target FROM edge_table');

/*************OUTPUT******************
 seq | node_seq | node | scc 
-----+----------+------+-----
   1 |        1 |    1 |   1 
   2 |        2 |    2 |   1 
   3 |        3 |    4 |   1 
   4 |        1 |    0 |   2 
   5 |        1 |    6 |   3 
   6 |        1 |    5 |   4 
   7 |        1 |    3 |   5
(7 rows)

*************************************/

