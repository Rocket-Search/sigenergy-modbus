//complie
//g++ -g -O3 -fPIC -Wall -std=c++20 -fpermissive -c -o sigenergy_modbus.o sigenergy_modbus.cpp;
//link
//g++ -O3 -fPIC -Wall -o sigenergy_modbus sigenergy_modbus.o -lmodbus
//Execute# ./sigenergy_modbus config_sigenergy_register_addresse_slave_247.cfg 247 192.168.188.69 502


#include <stdio.h>
#include "/usr/include/modbus/modbus.h"
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[]) 
{


	string config_file_pfad = argv[1];

	
	ifstream fileoperation_conf;


	fileoperation_conf.open(config_file_pfad.c_str(), ios::in);

	string config_parameter = "";
	string config_parameter_2 = "";
	vector<string> config_zeile;
		

	int semikolon_gefunden = -1;
	
	while (!fileoperation_conf.eof())
	{
		getline(fileoperation_conf, config_parameter);

		
		if (config_parameter == "")
		{

			continue;
		}
		
		config_zeile.push_back(config_parameter);
		
	}
	
	fileoperation_conf.close();





	string config_zeile_temp;
	string register_beschreibung;
	string register_adresse;
	string register_data_type;
	int register_adresse_int = -1;
	string register_anzahl;
	int register_anzahl_int = -1;
	int wo_ist_semikolon = - 1;

	
	
	string ip = argv[3];
	string port = argv[4];
	int port_int = -1;
	int rc = -1;
	
	
	
	
	port_int = stoi(port);
	modbus_t *ctx = modbus_new_tcp(ip.c_str(), port_int);
		
	
	string slave_address = argv[2];
	int slave_address_int = -1;
	slave_address_int = stoi(slave_address);
	
	rc = modbus_set_slave(ctx, slave_address_int);
	
	if (rc == -1) 
	{
		fprintf(stderr, "Invalid slave ID\n");
		modbus_free(ctx);
		return -1;
	}

    if (modbus_connect(ctx) == -1) 
    {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        return -1;
    }
    
	uint16_t tab_reg_u16[16];
	uint16_t tab_reg_u32[32];
	uint32_t tab_reg_real_u32;
	int16_t tab_reg_s32[32];
	int32_t tab_reg_real_s32;
	int16_t tab_reg_s16[16];
	char tab_reg_string_real[65];
	uint16_t tab_reg_u64[64];
	uint64_t tab_reg_real_u64;
	


	for (int i = 1; i < config_zeile.size(); i++)
	{
		
		
		
		
		
		config_zeile_temp = config_zeile[i];
		wo_ist_semikolon = config_zeile_temp.find(";");
		register_beschreibung = config_zeile_temp.substr(0,wo_ist_semikolon);
		register_beschreibung.erase(std::remove(register_beschreibung.begin(), register_beschreibung.end(), '\t'), register_beschreibung.end());
		
		config_zeile_temp = config_zeile_temp.substr(wo_ist_semikolon + 1, config_zeile_temp.size());
		
		
		
		wo_ist_semikolon = config_zeile_temp.find(";");
		register_adresse = config_zeile_temp.substr(0,wo_ist_semikolon);
		register_adresse.erase(std::remove(register_adresse.begin(), register_adresse.end(), '\t'), register_adresse.end());
		
		config_zeile_temp = config_zeile_temp.substr(wo_ist_semikolon + 1, config_zeile_temp.size());
		
		register_adresse_int=stoi(register_adresse);
		
		
		wo_ist_semikolon = config_zeile_temp.find(";");
		register_anzahl = config_zeile_temp.substr(0,wo_ist_semikolon);
		register_anzahl.erase(std::remove(register_anzahl.begin(), register_anzahl.end(), '\t'), register_anzahl.end());
		
		config_zeile_temp = config_zeile_temp.substr(wo_ist_semikolon + 1, config_zeile_temp.size());
		
		register_anzahl_int = stoi(register_anzahl);
		
		
		wo_ist_semikolon = config_zeile_temp.find(";");
		register_data_type = config_zeile_temp.substr(0,wo_ist_semikolon);
		register_data_type.erase(std::remove(register_data_type.begin(), register_data_type.end(), '\t'), register_data_type.end());
		
		config_zeile_temp = config_zeile_temp.substr(wo_ist_semikolon + 1, config_zeile_temp.size());
		
		
		
		
		
		
		
		
		
		
		cout<<"#################################################"<<endl;
		
		if (register_data_type == "S16")
		{
			rc = modbus_read_input_registers(ctx, register_adresse_int,register_anzahl_int , tab_reg_s16); 
			if (rc == -1) 
			{
				cout<<"#reg addr.#"<<register_adresse_int<<"#read error#"<<modbus_strerror(errno)<<"#"<<endl;
		
			}
			for (int i=0; i < rc; i++) 
			{
		
				cout<<register_beschreibung<<"#"<<tab_reg_s16[i]<<"#"<<endl;
			}
		}
		
		if (register_data_type == "S32")
		{
			rc = modbus_read_input_registers(ctx, register_adresse_int,register_anzahl_int , tab_reg_s32); 
			if (rc == -1) 
			{
		
				cout<<"#reg addr.#"<<register_adresse_int<<"#read error#"<<modbus_strerror(errno)<<"#"<<endl;
		
			}
			for (int i=0; i < rc; i++) 
			{
		
		
				tab_reg_real_s32 = (((int32_t)tab_reg_s32[i] << 16) | (int32_t)tab_reg_s32[i+1]);
				cout<<register_beschreibung<<"#"<<tab_reg_real_s32<<"#"<<endl;
		
			}
		}
		
		if (register_data_type == "U32")
		{
			rc = modbus_read_input_registers(ctx, register_adresse_int,register_anzahl_int , tab_reg_u32); 
			if (rc == -1) 
			{
				
				cout<<"#reg addr.#"<<register_adresse_int<<"#read error#"<<modbus_strerror(errno)<<"#"<<endl;
				
			}
			for (int i=0; i < rc; i++) 
			{
				
				
				tab_reg_real_u32 = (((uint32_t)tab_reg_u32[i] << 16) | (uint32_t)tab_reg_u32[i+1]);

				cout<<register_beschreibung<<"#"<<tab_reg_real_u32<<"#"<<endl;
			}
		}

		if (register_data_type == "U16")
		{
			rc = modbus_read_input_registers(ctx, register_adresse_int,register_anzahl_int , tab_reg_u16); 
			if (rc == -1) 
			{

				cout<<"#reg addr.#"<<register_adresse_int<<"#read error#"<<modbus_strerror(errno)<<"#"<<endl;

			}
			for (int i=0; i < rc; i++) 
			{


				cout<<register_beschreibung<<"#"<<tab_reg_u16[i]<<"#"<<endl;
			}
		}

		if (register_data_type == "STRING")
		{
			rc = modbus_read_input_registers(ctx, register_adresse_int,register_anzahl_int , tab_reg_u16); 
			if (rc == -1) 
			{

				cout<<"#reg addr.#"<<register_adresse_int<<"#read error#"<<modbus_strerror(errno)<<"#"<<endl;

			}

			for (int i = 0; i < rc; ++i) 
			{
				tab_reg_string_real[2 * i]     = tab_reg_u16[i] >> 8;
				tab_reg_string_real[2 * i + 1] = tab_reg_u16[i] & 0x00FF;
			}
			tab_reg_string_real[2 * rc] = '\0';

			cout<<register_beschreibung<<"#"<<tab_reg_string_real<<"#"<<endl;

		}

		if (register_data_type == "U64")
		{
			rc = modbus_read_input_registers(ctx, register_adresse_int,register_anzahl_int , tab_reg_u64); 
			if (rc == -1) 
			{

				cout<<"#reg addr.#"<<register_adresse_int<<"#read error#"<<modbus_strerror(errno)<<"#"<<endl;

			}
			for (int i=0; i < rc; i++) 
			{

				tab_reg_real_u64 = MODBUS_GET_INT64_FROM_INT16(tab_reg_u64, 0 );							

				cout<<register_beschreibung<<"#"<<tab_reg_real_u64<<"#"<<endl;
			}
		}

		cout<<"#################################################"<<endl;
	}






    modbus_close(ctx);
    modbus_free(ctx);

    return 0;
}
