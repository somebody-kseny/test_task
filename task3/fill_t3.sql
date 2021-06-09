USE test_db;
TRUNCATE table3;
DROP PROCEDURE IF EXISTS fill_t3;
DELIMITER //
CREATE PROCEDURE fill_t3()
BEGIN
DECLARE id_t2 INT;
DECLARE value_t2 CHAR(225);
DECLARE id_repeats INT;
DECLARE value_repeats CHAR(225);
DECLARE yet_not_exists BOOL DEFAULT TRUE;
DECLARE done INT DEFAULT FALSE;
DECLARE repeats CURSOR FOR
    SELECT table1.id, table2.value
    FROM table1, table2
    WHERE table1.value = table2.value
    AND table1.id = table2.id;
DECLARE t2 CURSOR FOR SELECT table2.id, table2.value FROM table2;
DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
INSERT table3 (id, value) SELECT id, value FROM table1;
OPEN t2;
copy_loop: LOOP
    FETCH t2 INTO id_t2, value_t2;
    IF done THEN LEAVE copy_loop;
    END IF;
    OPEN repeats;
    check_loop: LOOP
        FETCH repeats INTO id_repeats, value_repeats;
        IF done THEN
            SET done = false;
            LEAVE check_loop;
        END IF;
        IF ( id_repeats = id_t2 AND value_repeats = value_t2 ) THEN
            SET yet_not_exists = false;
            LEAVE check_loop;
        END IF;
    END LOOP;
    CLOSE repeats;
    if (yet_not_exists) THEN
        INSERT INTO table3 (id, value) VALUES (id_t2, value_t2);
        SET yet_not_exists = TRUE;
    END if;
    SET yet_not_exists = TRUE;
END LOOP;
CLOSE t2;
END;
//
CALL fill_t3()//
