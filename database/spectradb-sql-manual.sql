--
-- PostgreSQL database dump
--

-- Dumped from database version 9.4.4
-- Dumped by pg_dump version 9.4.4
-- Started on 2015-10-01 08:25:09

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- TOC entry 7 (class 2615 OID 16396)
-- Name: spectradb; Type: SCHEMA; Schema: -; Owner: CIMBUC
--

CREATE SCHEMA spectradb;


ALTER SCHEMA spectradb OWNER TO "CIMBUC";

--
-- TOC entry 189 (class 3079 OID 11855)
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- TOC entry 2122 (class 0 OID 0)
-- Dependencies: 189
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = spectradb, pg_catalog;

--
-- TOC entry 568 (class 1247 OID 16397)
-- Name: cedulas; Type: DOMAIN; Schema: spectradb; Owner: CIMBUC
--

CREATE DOMAIN cedulas AS character varying(10)
	CONSTRAINT cedulas_check CHECK (((VALUE)::text ~ '^[V|E]\d{1,10}$'::text));


ALTER DOMAIN cedulas OWNER TO "CIMBUC";

--
-- TOC entry 2123 (class 0 OID 0)
-- Dependencies: 568
-- Name: DOMAIN cedulas; Type: COMMENT; Schema: spectradb; Owner: CIMBUC
--

COMMENT ON DOMAIN cedulas IS 'Las cedulas solo pueden ser o Venezolanas (V) o extranjeras (E). Ejemplo:

V26845931
E65324920';


--
-- TOC entry 581 (class 1247 OID 16505)
-- Name: claves; Type: DOMAIN; Schema: spectradb; Owner: CIMBUC
--

CREATE DOMAIN claves AS character varying(16) NOT NULL
	CONSTRAINT claves_check CHECK (((VALUE)::text ~ '^((?=.*\d)(?=.*[a-z])(?=.*[A-Z]).{8,16})$'::text));


ALTER DOMAIN claves OWNER TO "CIMBUC";

--
-- TOC entry 2124 (class 0 OID 0)
-- Dependencies: 581
-- Name: DOMAIN claves; Type: COMMENT; Schema: spectradb; Owner: CIMBUC
--

COMMENT ON DOMAIN claves IS 'La clave debe comprender entre 8 y 16 caracteres, tener al menos 1 numero, 1 letra en mayuscula y 1 letra en minuscula.';


--
-- TOC entry 550 (class 1247 OID 16401)
-- Name: fechas; Type: DOMAIN; Schema: spectradb; Owner: CIMBUC
--

CREATE DOMAIN fechas AS character(10) NOT NULL
	CONSTRAINT fechas_check CHECK ((VALUE ~ '^(1[0-9][0-9][0-9]|2[0-9][0-9][0-9])-(0[1-9]|1[012])-(0[1-9]|1[0-9]|2[0-9]|3[01])$'::text));


ALTER DOMAIN fechas OWNER TO "CIMBUC";

--
-- TOC entry 2125 (class 0 OID 0)
-- Dependencies: 550
-- Name: DOMAIN fechas; Type: COMMENT; Schema: spectradb; Owner: CIMBUC
--

COMMENT ON DOMAIN fechas IS 'Las fechas deben tener el formato xxxx-xx-xx y deben comprenderse entre el anio 1000 y el anio 2999';


--
-- TOC entry 552 (class 1247 OID 16403)
-- Name: fototipos; Type: DOMAIN; Schema: spectradb; Owner: CIMBUC
--

CREATE DOMAIN fototipos AS character(1)
	CONSTRAINT fototipos_check CHECK (((((((VALUE ~ '1'::text) OR (VALUE ~ '2'::text)) OR (VALUE ~ '3'::text)) OR (VALUE ~ '4'::text)) OR (VALUE ~ '5'::text)) OR (VALUE ~ '6'::text)));


ALTER DOMAIN fototipos OWNER TO "CIMBUC";

--
-- TOC entry 554 (class 1247 OID 16405)
-- Name: generos; Type: DOMAIN; Schema: spectradb; Owner: CIMBUC
--

CREATE DOMAIN generos AS character(1) NOT NULL
	CONSTRAINT generos_check CHECK (((VALUE ~ 'M'::text) OR (VALUE ~ 'F'::text)));


ALTER DOMAIN generos OWNER TO "CIMBUC";

--
-- TOC entry 593 (class 1247 OID 33033)
-- Name: palabras; Type: DOMAIN; Schema: spectradb; Owner: CIMBUC
--

CREATE DOMAIN palabras AS character varying NOT NULL
	CONSTRAINT palabras_check CHECK (((VALUE)::text ~ '^([A-Z]+([ ]?[A-Z]?[A-Z]+)*)$'::text));


ALTER DOMAIN palabras OWNER TO "CIMBUC";

--
-- TOC entry 556 (class 1247 OID 16411)
-- Name: roles; Type: DOMAIN; Schema: spectradb; Owner: CIMBUC
--

CREATE DOMAIN roles AS character varying(15) NOT NULL
	CONSTRAINT roles_check CHECK (((((VALUE)::text ~ 'dermatologo'::text) OR ((VALUE)::text ~ 'investigador'::text)) OR ((VALUE)::text ~ 'administrador'::text)));


ALTER DOMAIN roles OWNER TO "CIMBUC";

--
-- TOC entry 558 (class 1247 OID 16413)
-- Name: tipos_muestras; Type: DOMAIN; Schema: spectradb; Owner: CIMBUC
--

CREATE DOMAIN tipos_muestras AS character varying(10) NOT NULL
	CONSTRAINT tipos_muestras_check CHECK ((((VALUE)::text ~ 'fototipo'::text) OR ((VALUE)::text ~ 'lesion'::text)));


ALTER DOMAIN tipos_muestras OWNER TO "CIMBUC";

SET search_path = spectradb, pg_catalog;

--
-- TOC entry 207 (class 1255 OID 41348)
-- Name: revisar_actualizacion_historia(); Type: FUNCTION; Schema: spectradb; Owner: postgres
--

CREATE FUNCTION revisar_actualizacion_historia() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	IF OLD.fecha_ingreso != NEW.fecha_ingreso THEN
		RAISE EXCEPTION 'No se puede modificar la fecha de ingreso de una historia.';
		RETURN NULL;
	ELSE
		RETURN NEW;
	END IF;
END;
$$;


ALTER FUNCTION spectradb.revisar_actualizacion_historia() OWNER TO postgres;

--
-- TOC entry 206 (class 1255 OID 33135)
-- Name: revisar_actualizacion_muestra(); Type: FUNCTION; Schema: spectradb; Owner: postgres
--

CREATE FUNCTION revisar_actualizacion_muestra() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
DECLARE
	correcto boolean := true;
BEGIN
	IF OLD.tipo_muestra != NEW.tipo_muestra THEN

		RAISE EXCEPTION 'No se puede modificar el tipo de una muestra.';
		correcto := false;
	END IF;

	IF OLD.nombre_muestra = 'FOTOTIPO' AND NEW.nombre_muestra != 'FOTOTIPO' THEN

		RAISE EXCEPTION 'No se puede modificar el nombre de una muestra de tipo fototipo.';
		correcto := false;
	END IF;

	IF OLD.fecha_muestra != NEW.fecha_muestra THEN
		RAISE EXCEPTION 'No se puede modificar la fecha de registro de una muestra.';
		correcto := false;
	END IF;

	IF OLD.usuario!= NEW.usuario THEN
		RAISE EXCEPTION 'No se puede modificar el usuario que registró la muestra.';
		correcto := false;
	END IF;

	IF OLD.historia != NEW.historia THEN
		RAISE EXCEPTION 'No se puede modificar la historia a la que pertenece la muestra.';
		correcto := false;
	END IF;

	IF OLD.datos_espectrales != NEW.datos_espectrales THEN
		RAISE EXCEPTION 'No se pueden modificar los datos espectrales pertenecientes a la muestra.';
		correcto := false;
	END IF;

	IF correcto THEN
		RETURN NEW;
	ELSE
		RETURN NULL;
	END IF;
END;
$$;


ALTER FUNCTION spectradb.revisar_actualizacion_muestra() OWNER TO postgres;

--
-- TOC entry 203 (class 1255 OID 33133)
-- Name: revisar_actualizacion_usuario(); Type: FUNCTION; Schema: spectradb; Owner: postgres
--

CREATE FUNCTION revisar_actualizacion_usuario() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
DECLARE
	resultado integer;
BEGIN
	IF OLD.rol = 'administrador' AND NEW.rol != 'administrador' THEN
		SELECT count(*) INTO resultado FROM spectradb.usuario WHERE rol = 'administrador';

		IF resultado = 1 THEN
			RAISE EXCEPTION 'Sólo queda 1 usuario administrador, no se realizará la actualización.';
			RETURN NULL;
		ELSE
			RETURN NEW;
		END IF;
	ELSE
		RETURN NEW;
	END IF;
END;
$$;


ALTER FUNCTION spectradb.revisar_actualizacion_usuario() OWNER TO postgres;

--
-- TOC entry 205 (class 1255 OID 33128)
-- Name: revisar_eliminacion_muestra(); Type: FUNCTION; Schema: spectradb; Owner: postgres
--

CREATE FUNCTION revisar_eliminacion_muestra() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	DELETE FROM spectradb.datos_espectrales WHERE id_datos_espectrales = OLD.datos_espectrales;
	
	IF OLD.tipo_muestra = 'fototipo' THEN
		UPDATE spectradb.historia SET fototipo = NULL WHERE id_historia = OLD.historia;
	END IF;

	RETURN OLD;
END;
$$;


ALTER FUNCTION spectradb.revisar_eliminacion_muestra() OWNER TO postgres;

--
-- TOC entry 204 (class 1255 OID 33131)
-- Name: revisar_eliminacion_usuario(); Type: FUNCTION; Schema: spectradb; Owner: postgres
--

CREATE FUNCTION revisar_eliminacion_usuario() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
DECLARE
	resultado integer;
BEGIN
	IF OLD.rol = 'administrador' THEN
		SELECT count(*) INTO resultado FROM spectradb.usuario WHERE rol = 'administrador';

		IF resultado = 1 THEN
			RAISE EXCEPTION 'Sólo queda 1 usuario administrador, no se realizará la eliminación.';
			RETURN NULL;
		ELSE
			RETURN OLD;
		END IF;
	ELSE
		RETURN OLD;
	END IF;
END;
$$;


ALTER FUNCTION spectradb.revisar_eliminacion_usuario() OWNER TO postgres;

--
-- TOC entry 202 (class 1255 OID 33111)
-- Name: revisar_insercion(); Type: FUNCTION; Schema: spectradb; Owner: postgres
--

CREATE FUNCTION revisar_insercion() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
BEGIN
	IF NEW.tipo_muestra = 'lesion' THEN
		RETURN NEW;
	ELSE
		SELECT * FROM muestra WHERE historia = NEW.historia AND tipo_muestra = 'fototipo';
		IF NO_DATA_FOUND THEN
			RETURN NEW;
		ELSE
			RAISE EXCEPTION 'Ya existe una muestra de fototipo para la historia: %', NEW.historia USING ERRCODE = '23505';
			RETURN NULL;
		END IF;
	END IF;
END;
$$;


ALTER FUNCTION spectradb.revisar_insercion() OWNER TO postgres;

--
-- TOC entry 208 (class 1255 OID 33113)
-- Name: revisar_insercion_muestra(); Type: FUNCTION; Schema: CIMBUC; Owner: postgres
--

CREATE FUNCTION revisar_insercion_muestra() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
DECLARE
	resultado integer;
	rol_usuario varchar;
BEGIN

	SELECT rol INTO rol_usuario FROM spectradb.usuario WHERE cedula = NEW.usuario;

	IF rol_usuario = 'dermatologo' THEN

		IF NEW.tipo_muestra = 'lesion' THEN
			RETURN NEW;
		ELSE
			SELECT id_muestra INTO resultado FROM spectradb.muestra WHERE historia = NEW.historia AND tipo_muestra = 'fototipo';
			IF NOT FOUND THEN

				IF NEW.nombre_muestra != 'FOTOTIPO' THEN
					NEW.nombre_muestra := 'FOTOTIPO';
				END IF;
			
				RETURN NEW;
			ELSE
				RAISE EXCEPTION 'Ya existe una muestra de fototipo para esta historia.';
				RETURN NULL;
			END IF;
		END IF;

	ELSE
		RAISE EXCEPTION 'Sólo los usuarios dermatólogos pueden registrar una historia.';
		RETURN NULL;
	END IF;
END;
$$;


ALTER FUNCTION spectradb.revisar_insercion_muestra() OWNER TO postgres;

SET search_path = spectradb, pg_catalog;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- TOC entry 185 (class 1259 OID 41358)
-- Name: datos_absorcion; Type: TABLE; Schema: spectradb; Owner: CIMBUC; Tablespace: 
--

CREATE TABLE datos_absorcion (
    nm_400 real NOT NULL,
    nm_410 real NOT NULL,
    nm_420 real NOT NULL,
    nm_430 real NOT NULL,
    nm_440 real NOT NULL,
    nm_450 real NOT NULL,
    nm_460 real NOT NULL,
    nm_470 real NOT NULL,
    nm_480 real NOT NULL,
    nm_490 real NOT NULL,
    nm_500 real NOT NULL,
    nm_510 real NOT NULL,
    nm_520 real NOT NULL,
    nm_530 real NOT NULL,
    nm_540 real NOT NULL,
    nm_550 real NOT NULL,
    nm_560 real NOT NULL,
    nm_570 real NOT NULL,
    nm_580 real NOT NULL,
    nm_590 real NOT NULL,
    nm_600 real NOT NULL,
    nm_610 real NOT NULL,
    nm_620 real NOT NULL,
    nm_630 real NOT NULL,
    nm_640 real NOT NULL,
    nm_650 real NOT NULL,
    nm_660 real NOT NULL,
    nm_670 real NOT NULL,
    nm_680 real NOT NULL,
    nm_690 real NOT NULL,
    nm_700 real NOT NULL,
    id_datos_absorcion integer NOT NULL,
    datos_espectrales integer NOT NULL
);


ALTER TABLE datos_absorcion OWNER TO "CIMBUC";

--
-- TOC entry 186 (class 1259 OID 41372)
-- Name: datos_absorcion_datos_espectrales_seq; Type: SEQUENCE; Schema: spectradb; Owner: CIMBUC
--

CREATE SEQUENCE datos_absorcion_datos_espectrales_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE datos_absorcion_datos_espectrales_seq OWNER TO "CIMBUC";

--
-- TOC entry 2126 (class 0 OID 0)
-- Dependencies: 186
-- Name: datos_absorcion_datos_espectrales_seq; Type: SEQUENCE OWNED BY; Schema: spectradb; Owner: CIMBUC
--

ALTER SEQUENCE datos_absorcion_datos_espectrales_seq OWNED BY datos_absorcion.datos_espectrales;


--
-- TOC entry 184 (class 1259 OID 41356)
-- Name: datos_absorcion_id_datos_absorcion_seq; Type: SEQUENCE; Schema: spectradb; Owner: CIMBUC
--

CREATE SEQUENCE datos_absorcion_id_datos_absorcion_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE datos_absorcion_id_datos_absorcion_seq OWNER TO "CIMBUC";

--
-- TOC entry 2127 (class 0 OID 0)
-- Dependencies: 184
-- Name: datos_absorcion_id_datos_absorcion_seq; Type: SEQUENCE OWNED BY; Schema: spectradb; Owner: CIMBUC
--

ALTER SEQUENCE datos_absorcion_id_datos_absorcion_seq OWNED BY datos_absorcion.id_datos_absorcion;


--
-- TOC entry 173 (class 1259 OID 16415)
-- Name: datos_adicionales; Type: TABLE; Schema: spectradb; Owner: CIMBUC; Tablespace: 
--

CREATE TABLE datos_adicionales (
    cie_x real NOT NULL,
    cie_y real NOT NULL,
    cie_z real NOT NULL,
    cie_l real NOT NULL,
    cie_a real NOT NULL,
    cie_b real NOT NULL,
    indice_eritema real NOT NULL,
    id_datos_adicionales integer NOT NULL,
    datos_espectrales integer NOT NULL
);


ALTER TABLE datos_adicionales OWNER TO "CIMBUC";

--
-- TOC entry 174 (class 1259 OID 16418)
-- Name: datos_adicionales_id_datos_adicionales_seq; Type: SEQUENCE; Schema: spectradb; Owner: CIMBUC
--

CREATE SEQUENCE datos_adicionales_id_datos_adicionales_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE datos_adicionales_id_datos_adicionales_seq OWNER TO "CIMBUC";

--
-- TOC entry 2128 (class 0 OID 0)
-- Dependencies: 174
-- Name: datos_adicionales_id_datos_adicionales_seq; Type: SEQUENCE OWNED BY; Schema: spectradb; Owner: CIMBUC
--

ALTER SEQUENCE datos_adicionales_id_datos_adicionales_seq OWNED BY datos_adicionales.id_datos_adicionales;

CREATE TABLE datos_espectrales (
    nm_400 real NOT NULL,
    nm_410 real NOT NULL,
    nm_420 real NOT NULL,
    nm_430 real NOT NULL,
    nm_440 real NOT NULL,
    nm_450 real NOT NULL,
    nm_460 real NOT NULL,
    nm_470 real NOT NULL,
    nm_480 real NOT NULL,
    nm_490 real NOT NULL,
    nm_500 real NOT NULL,
    nm_510 real NOT NULL,
    nm_520 real NOT NULL,
    nm_530 real NOT NULL,
    nm_540 real NOT NULL,
    nm_550 real NOT NULL,
    nm_560 real NOT NULL,
    nm_570 real NOT NULL,
    nm_580 real NOT NULL,
    nm_590 real NOT NULL,
    nm_600 real NOT NULL,
    nm_610 real NOT NULL,
    nm_620 real NOT NULL,
    nm_630 real NOT NULL,
    nm_640 real NOT NULL,
    nm_650 real NOT NULL,
    nm_660 real NOT NULL,
    nm_670 real NOT NULL,
    nm_680 real NOT NULL,
    nm_690 real NOT NULL,
    nm_700 real NOT NULL,
    id_datos_espectrales integer NOT NULL
);


ALTER TABLE datos_espectrales OWNER TO "CIMBUC";

--
-- TOC entry 176 (class 1259 OID 16423)
-- Name: datos_espectrales_id_datos_espectrales_seq; Type: SEQUENCE; Schema: spectradb; Owner: CIMBUC
--

CREATE SEQUENCE datos_espectrales_id_datos_espectrales_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE datos_espectrales_id_datos_espectrales_seq OWNER TO "CIMBUC";

--
-- TOC entry 2130 (class 0 OID 0)
-- Dependencies: 176
-- Name: datos_espectrales_id_datos_espectrales_seq; Type: SEQUENCE OWNED BY; Schema: spectradb; Owner: CIMBUC
--

ALTER SEQUENCE datos_espectrales_id_datos_espectrales_seq OWNED BY datos_espectrales.id_datos_espectrales;


--
-- TOC entry 177 (class 1259 OID 16425)
-- Name: historia; Type: TABLE; Schema: spectradb; Owner: CIMBUC; Tablespace: 
--

CREATE TABLE historia (
    cedula cedulas,
    nombre palabras NOT NULL,
    apellido palabras NOT NULL,
    fecha_nac fechas NOT NULL,
    fecha_ingreso fechas NOT NULL,
    sexo generos NOT NULL,
    fototipo fototipos,
    id_historia integer NOT NULL
);


ALTER TABLE historia OWNER TO "CIMBUC";

--
-- TOC entry 181 (class 1259 OID 32901)
-- Name: historia_id_historia_seq; Type: SEQUENCE; Schema: spectradb; Owner: CIMBUC
--

CREATE SEQUENCE historia_id_historia_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE historia_id_historia_seq OWNER TO "CIMBUC";

--
-- TOC entry 2131 (class 0 OID 0)
-- Dependencies: 181
-- Name: historia_id_historia_seq; Type: SEQUENCE OWNED BY; Schema: spectradb; Owner: CIMBUC
--

ALTER SEQUENCE historia_id_historia_seq OWNED BY historia.id_historia;


--
-- TOC entry 178 (class 1259 OID 16439)
-- Name: muestra; Type: TABLE; Schema: spectradb; Owner: CIMBUC; Tablespace: 
--

CREATE TABLE muestra (
    id_muestra integer NOT NULL,
    tipo_muestra tipos_muestras NOT NULL,
    fecha_muestra fechas NOT NULL,
    nombre_muestra palabras NOT NULL,
    area_muestra palabras NOT NULL,
    observaciones text,
    usuario cedulas NOT NULL,
    historia integer NOT NULL,
    datos_espectrales integer NOT NULL
);


ALTER TABLE muestra OWNER TO "CIMBUC";

--
-- TOC entry 2132 (class 0 OID 0)
-- Dependencies: 178
-- Name: TABLE muestra; Type: COMMENT; Schema: spectradb; Owner: CIMBUC
--

COMMENT ON TABLE muestra IS 'Esta tabla almacena los datos de una muestra, la cual es tomada por un usuario y perteneciente a una historia';


--
-- TOC entry 183 (class 1259 OID 41325)
-- Name: muestra_datos_espectrales_seq; Type: SEQUENCE; Schema: spectradb; Owner: CIMBUC
--

CREATE SEQUENCE muestra_datos_espectrales_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE muestra_datos_espectrales_seq OWNER TO "CIMBUC";

--
-- TOC entry 2133 (class 0 OID 0)
-- Dependencies: 183
-- Name: muestra_datos_espectrales_seq; Type: SEQUENCE OWNED BY; Schema: spectradb; Owner: CIMBUC
--

ALTER SEQUENCE muestra_datos_espectrales_seq OWNED BY muestra.datos_espectrales;


--
-- TOC entry 182 (class 1259 OID 32912)
-- Name: muestra_historia_seq; Type: SEQUENCE; Schema: spectradb; Owner: CIMBUC
--

CREATE SEQUENCE muestra_historia_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE muestra_historia_seq OWNER TO "CIMBUC";

--
-- TOC entry 2134 (class 0 OID 0)
-- Dependencies: 182
-- Name: muestra_historia_seq; Type: SEQUENCE OWNED BY; Schema: spectradb; Owner: CIMBUC
--

ALTER SEQUENCE muestra_historia_seq OWNED BY muestra.historia;


--
-- TOC entry 179 (class 1259 OID 16445)
-- Name: muestra_id_muestra_seq; Type: SEQUENCE; Schema: spectradb; Owner: CIMBUC
--

CREATE SEQUENCE muestra_id_muestra_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE muestra_id_muestra_seq OWNER TO "CIMBUC";

--
-- TOC entry 2135 (class 0 OID 0)
-- Dependencies: 179
-- Name: muestra_id_muestra_seq; Type: SEQUENCE OWNED BY; Schema: spectradb; Owner: CIMBUC
--

ALTER SEQUENCE muestra_id_muestra_seq OWNED BY muestra.id_muestra;


--
-- TOC entry 180 (class 1259 OID 16447)
-- Name: usuario; Type: TABLE; Schema: spectradb; Owner: CIMBUC; Tablespace: 
--

CREATE TABLE usuario (
    cedula cedulas NOT NULL,
    nombre palabras NOT NULL,
    apellido palabras NOT NULL,
    fecha_nac fechas NOT NULL,
    clave claves NOT NULL,
    rol roles NOT NULL,
    sexo generos NOT NULL
);


ALTER TABLE usuario OWNER TO "CIMBUC";

--
-- TOC entry 2136 (class 0 OID 0)
-- Dependencies: 180
-- Name: TABLE usuario; Type: COMMENT; Schema: spectradb; Owner: CIMBUC
--

COMMENT ON TABLE usuario IS 'Esta tabla almacena los datos de un usuario';


--
-- TOC entry 1952 (class 2604 OID 41361)
-- Name: id_datos_absorcion; Type: DEFAULT; Schema: spectradb; Owner: CIMBUC
--

ALTER TABLE ONLY datos_absorcion ALTER COLUMN id_datos_absorcion SET DEFAULT nextval('datos_absorcion_id_datos_absorcion_seq'::regclass);


--
-- TOC entry 1948 (class 2604 OID 16453)
-- Name: id_datos_adicionales; Type: DEFAULT; Schema: spectradb; Owner: CIMBUC
--

ALTER TABLE ONLY datos_adicionales ALTER COLUMN id_datos_adicionales SET DEFAULT nextval('datos_adicionales_id_datos_adicionales_seq'::regclass);


--
-- TOC entry 1949 (class 2604 OID 16454)
-- Name: id_datos_espectrales; Type: DEFAULT; Schema: spectradb; Owner: CIMBUC
--

ALTER TABLE ONLY datos_espectrales ALTER COLUMN id_datos_espectrales SET DEFAULT nextval('datos_espectrales_id_datos_espectrales_seq'::regclass);


--
-- TOC entry 1950 (class 2604 OID 32903)
-- Name: id_historia; Type: DEFAULT; Schema: spectradb; Owner: CIMBUC
--

ALTER TABLE ONLY historia ALTER COLUMN id_historia SET DEFAULT nextval('historia_id_historia_seq'::regclass);


--
-- TOC entry 1951 (class 2604 OID 16456)
-- Name: id_muestra; Type: DEFAULT; Schema: spectradb; Owner: CIMBUC
--

ALTER TABLE ONLY muestra ALTER COLUMN id_muestra SET DEFAULT nextval('muestra_id_muestra_seq'::regclass);


--
-- TOC entry 1971 (class 2606 OID 41406)
-- Name: datos_absorcion_datos_espectrales_key; Type: CONSTRAINT; Schema: spectradb; Owner: CIMBUC; Tablespace: 
--

ALTER TABLE ONLY datos_absorcion
    ADD CONSTRAINT datos_absorcion_datos_espectrales_key UNIQUE (datos_espectrales);


--
-- TOC entry 1973 (class 2606 OID 41363)
-- Name: datos_absorcion_pkey; Type: CONSTRAINT; Schema: spectradb; Owner: CIMBUC; Tablespace: 
--

ALTER TABLE ONLY datos_absorcion
    ADD CONSTRAINT datos_absorcion_pkey PRIMARY KEY (id_datos_absorcion);


--
-- TOC entry 1955 (class 2606 OID 33108)
-- Name: datos_adicionales_datos_espectrales_key; Type: CONSTRAINT; Schema: spectradb; Owner: CIMBUC; Tablespace: 
--

ALTER TABLE ONLY datos_adicionales
    ADD CONSTRAINT datos_adicionales_datos_espectrales_key UNIQUE (datos_espectrales);


--
-- TOC entry 1957 (class 2606 OID 16458)
-- Name: datos_adicionales_pkey; Type: CONSTRAINT; Schema: spectradb; Owner: CIMBUC; Tablespace: 
--

ALTER TABLE ONLY datos_adicionales
    ADD CONSTRAINT datos_adicionales_pkey PRIMARY KEY (id_datos_adicionales);


--
-- TOC entry 1959 (class 2606 OID 16460)
-- Name: datos_espectrales_pkey; Type: CONSTRAINT; Schema: spectradb; Owner: CIMBUC; Tablespace: 
--

ALTER TABLE ONLY datos_espectrales
    ADD CONSTRAINT datos_espectrales_pkey PRIMARY KEY (id_datos_espectrales);


--
-- TOC entry 1961 (class 2606 OID 33104)
-- Name: historia_medica_cedula_key; Type: CONSTRAINT; Schema: spectradb; Owner: CIMBUC; Tablespace: 
--

ALTER TABLE ONLY historia
    ADD CONSTRAINT historia_medica_cedula_key UNIQUE (cedula);


--
-- TOC entry 1963 (class 2606 OID 32911)
-- Name: historia_medica_pkey; Type: CONSTRAINT; Schema: spectradb; Owner: CIMBUC; Tablespace: 
--

ALTER TABLE ONLY historia
    ADD CONSTRAINT historia_medica_pkey PRIMARY KEY (id_historia);


--
-- TOC entry 1965 (class 2606 OID 41329)
-- Name: muestra_datos_espectrales_key; Type: CONSTRAINT; Schema: spectradb; Owner: CIMBUC; Tablespace: 
--

ALTER TABLE ONLY muestra
    ADD CONSTRAINT muestra_datos_espectrales_key UNIQUE (datos_espectrales);


--
-- TOC entry 1967 (class 2606 OID 16466)
-- Name: muestra_pkey; Type: CONSTRAINT; Schema: spectradb; Owner: CIMBUC; Tablespace: 
--

ALTER TABLE ONLY muestra
    ADD CONSTRAINT muestra_pkey PRIMARY KEY (id_muestra);


--
-- TOC entry 1969 (class 2606 OID 16468)
-- Name: usuario_pkey; Type: CONSTRAINT; Schema: spectradb; Owner: CIMBUC; Tablespace: 
--

ALTER TABLE ONLY usuario
    ADD CONSTRAINT usuario_pkey PRIMARY KEY (cedula);


--
-- TOC entry 1984 (class 2620 OID 41349)
-- Name: actualizacion_historia; Type: TRIGGER; Schema: spectradb; Owner: CIMBUC
--

CREATE TRIGGER actualizacion_historia BEFORE UPDATE ON historia FOR EACH ROW EXECUTE PROCEDURE spectradb.revisar_actualizacion_historia();


--
-- TOC entry 1987 (class 2620 OID 33136)
-- Name: actualizacion_muestra; Type: TRIGGER; Schema: spectradb; Owner: CIMBUC
--

CREATE TRIGGER actualizacion_muestra BEFORE UPDATE ON muestra FOR EACH ROW EXECUTE PROCEDURE spectradb.revisar_actualizacion_muestra();


--
-- TOC entry 1989 (class 2620 OID 33134)
-- Name: actualizacion_usuario; Type: TRIGGER; Schema: spectradb; Owner: CIMBUC
--

CREATE TRIGGER actualizacion_usuario BEFORE UPDATE ON usuario FOR EACH ROW EXECUTE PROCEDURE spectradb.revisar_actualizacion_usuario();


--
-- TOC entry 1986 (class 2620 OID 33129)
-- Name: eliminacion_muestra; Type: TRIGGER; Schema: spectradb; Owner: CIMBUC
--

CREATE TRIGGER eliminacion_muestra AFTER DELETE ON muestra FOR EACH ROW EXECUTE PROCEDURE spectradb.revisar_eliminacion_muestra();


--
-- TOC entry 1988 (class 2620 OID 33132)
-- Name: eliminacion_usuario; Type: TRIGGER; Schema: spectradb; Owner: CIMBUC
--

CREATE TRIGGER eliminacion_usuario BEFORE DELETE ON usuario FOR EACH ROW EXECUTE PROCEDURE spectradb.revisar_eliminacion_usuario();


--
-- TOC entry 1985 (class 2620 OID 33114)
-- Name: insercion_muestra; Type: TRIGGER; Schema: spectradb; Owner: CIMBUC
--

CREATE TRIGGER insercion_muestra BEFORE INSERT ON muestra FOR EACH ROW EXECUTE PROCEDURE spectradb.revisar_insercion_muestra();


--
-- TOC entry 1982 (class 2606 OID 41395)
-- Name: datos_absorcion_datos_espectrales_fkey; Type: FK CONSTRAINT; Schema: spectradb; Owner: CIMBUC
--

ALTER TABLE ONLY datos_absorcion
    ADD CONSTRAINT datos_absorcion_datos_espectrales_fkey FOREIGN KEY (datos_espectrales) REFERENCES datos_espectrales(id_datos_espectrales) ON DELETE CASCADE;


--
-- TOC entry 1978 (class 2606 OID 24707)
-- Name: datos_adicionales_datos_espectrales_fkey; Type: FK CONSTRAINT; Schema: spectradb; Owner: CIMBUC
--

ALTER TABLE ONLY datos_adicionales
    ADD CONSTRAINT datos_adicionales_datos_espectrales_fkey FOREIGN KEY (datos_espectrales) REFERENCES datos_espectrales(id_datos_espectrales) ON DELETE CASCADE;


--
-- TOC entry 1981 (class 2606 OID 41343)
-- Name: muestra_datos_espectrales_fkey; Type: FK CONSTRAINT; Schema: spectradb; Owner: CIMBUC
--

ALTER TABLE ONLY muestra
    ADD CONSTRAINT muestra_datos_espectrales_fkey FOREIGN KEY (datos_espectrales) REFERENCES datos_espectrales(id_datos_espectrales) ON DELETE CASCADE;


--
-- TOC entry 1980 (class 2606 OID 32915)
-- Name: muestra_historia_fkey; Type: FK CONSTRAINT; Schema: spectradb; Owner: CIMBUC
--

ALTER TABLE ONLY muestra
    ADD CONSTRAINT muestra_historia_fkey FOREIGN KEY (historia) REFERENCES historia(id_historia) ON DELETE CASCADE;


--
-- TOC entry 1979 (class 2606 OID 16547)
-- Name: muestra_usuario_fkey; Type: FK CONSTRAINT; Schema: spectradb; Owner: CIMBUC
--

ALTER TABLE ONLY muestra
    ADD CONSTRAINT muestra_usuario_fkey FOREIGN KEY (usuario) REFERENCES usuario(cedula) ON DELETE CASCADE;


-- Completed on 2015-10-01 08:25:09

--
-- PostgreSQL database dump complete
--