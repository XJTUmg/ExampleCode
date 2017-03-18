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
(0, 2), (2, 3),
(2, 4), (3, 4),
(5, 6), (6, 7),
(8, 9), (9, 10),
(10, 8);

SELECT * FROM pgr_biconnectedComponents (
	'SELECT id, source, target FROM edge_table');

/*************OUTPUT******************
 seq | edge_seq | edge | edge_p1 | edge_p2 | bcc 
-----+----------+------+---------+---------+-----
   1 |        1 |    4 |       2 |       3 |   1
   2 |        2 |    5 |       2 |       4 |   1
   3 |        3 |    6 |       3 |       4 |   1
   4 |        1 |    1 |       0 |       1 |   2
   5 |        2 |    2 |       1 |       2 |   2
   6 |        3 |    3 |       0 |       2 |   2
   7 |        1 |    7 |       5 |       6 |   3
   8 |        1 |    8 |       6 |       7 |   4
   9 |        1 |    9 |       8 |       9 |   5
  10 |        2 |   10 |       9 |      10 |   5
  11 |        3 |   11 |       8 |      10 |   5
(11 rows)
*************************************/

