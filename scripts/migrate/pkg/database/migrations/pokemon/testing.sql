-- +migrate Up

INSERT INTO public.base_stats(
	base_stats_id, hp, attack, defence, speed, sp_attack, sp_defence)
	VALUES (0, 1, 1, 1, 1, 1, 1);

INSERT INTO public.element_types(
	element_type_id, element_0, element_1)
	VALUES (0, 3, 5);

INSERT INTO public.pokemon(
	pokedex_no, gender, nature, icon_path, name, base_stats_id, evolve_level, evolve_pokemon, element_type_id)
	VALUES (0, 0, 0, 'kek', 'Lapras', 0, 69, 0, 0);

INSERT INTO public.pokemon(
	pokedex_no, gender, nature, icon_path, name, base_stats_id, evolve_level, evolve_pokemon, element_type_id)
	VALUES (1, 0, 0, 'kek', 'Gyarados', 0, 69, 0, 0);

INSERT INTO public.pokemon(
	pokedex_no, gender, nature, icon_path, name, base_stats_id, evolve_level, evolve_pokemon, element_type_id)
	VALUES (2, 0, 0, 'ono', 'Zapados', 0, 420, 0, 0);

INSERT INTO player.move(
	move_id, name, element_type, damage, accuracy, max_pp)
	VALUES (0, 'Tackle', 5, 100, 60, 24);

INSERT INTO player.ev_stats(
	ev_id, hp, attack, defence, speed, sp_attack, sp_defence)
	VALUES (0, 2, 2, 2, 2, 2, 2);

INSERT INTO player.iv_stats(
	iv_id, hp, attack, defence, speed, sp_attack, sp_defence)
	VALUES (0, 3, 3, 3, 3, 3, 3);

INSERT INTO player.user_pokemon(
	pokemon_id, pokedex_no, ev_id, iv_id, nickname, level)
	VALUES (69, 0, 0, 0, 'Lapras', 420);

INSERT INTO player.user_pokemon(
	pokemon_id, pokedex_no, ev_id, iv_id, nickname, level)
	VALUES (70, 1, 0, 0, 'Gyarados', 420);

INSERT INTO player.user_pokemon(
	pokemon_id, pokedex_no, ev_id, iv_id, nickname, level)
	VALUES (71, 2, 0, 0, 'Zapados', 420);

INSERT INTO player.player_move_bridge(
	generated_id, move_id, pokemon_id, position)
	VALUES (0, 0, 69, 0);

INSERT INTO player.player_move_bridge(
	generated_id, move_id, pokemon_id, position)
	VALUES (1, 0, 70, 0);

INSERT INTO player.player_move_bridge(
	generated_id, move_id, pokemon_id, position)
	VALUES (2, 0, 71, 0);

INSERT INTO player.team(
	team_id, pokemon_id_0, pokemon_id_1, pokemon_id_2, pokemon_id_3, pokemon_id_4, pokemon_id_5)
	VALUES (0, 69, 70, 71, NULL, NULL, NULL);

INSERT INTO player.player(
	player_id, team_id, name, gender, pkc)
	VALUES (0, 0, 'Ovenoboyo', 1, 69420);



