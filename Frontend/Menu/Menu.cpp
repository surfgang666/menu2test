#include "Menu.h"
#include "../Renderer/Renderer.h"

#include <algorithm>
#include "../../../config/config.h"
#include "../../../lua/Clua.h"
#include "../../../unity.h"

using namespace IdaLovesMe;

/// <summary>
/// Initialize GTX, and preset some stuff.
/// Called only once at the beginning.
/// </summary>
void CMenu::Initialize() 
{
	if (this->m_bInitialized)
		return;

	ui::CreateContext();
	GuiContext* g = Globals::Gui_Ctx;
	g->ItemSpacing = Vec2(0, 6);
	g->MenuAlpha = 1;

	this->m_bIsOpened = true;
	this->m_bInitialized = true;
}

/// <summary>
/// Drawing the user interface.
/// Please keep in mind that this function is called on each frame.
/// </summary>
void CMenu::Draw()
{
	static float alpha = 0.f;
	float fc = ImGui::GetIO().DeltaTime * 255 * 10;
	if (!this->m_bIsOpened && alpha > 0.f)
		alpha = std::clamp(alpha - fc / 255.f, 0.f, 1.f);

	if (this->m_bIsOpened && alpha < 1.f)
		alpha = std::clamp(alpha + fc / 255.f, 0.f, 1.f);

	Globals::Gui_Ctx->MenuAlpha = static_cast<int>(floor(alpha * 255));

	if (!this->m_bIsOpened && alpha == 0.f)
		return;

	ui::GetInputFromWindow(Render::Draw->GetWindow());

	ui::SetNextWindowSize({ 660,560 });
	ui::Begin("Main", GuiFlags_None);

	ui::TabButton("A", &this->m_nCurrentTab, 0, 7);
	ui::TabButton("G", &this->m_nCurrentTab, 1, 7);
	ui::TabButton("C", &this->m_nCurrentTab, 2, 7);
	ui::TabButton("D", &this->m_nCurrentTab, 3, 7);
	ui::TabButton("E", &this->m_nCurrentTab, 4, 7);
	ui::TabButton("F", &this->m_nCurrentTab, 5, 7);
	ui::TabButton("H", &this->m_nCurrentTab, 6, 7);
	ui::TabButton("I", &this->m_nCurrentTab, 7, 7);

	switch(this->m_nCurrentTab)
	{
		
		//
		// RAGE
		//
		case 0:
		{
			ui::BeginChild("Other#Rage", { Vec2(6, 0), Vec2(3, 10) });
			{
				ui::SingleSelect("Accuracy boost", &g_config->aimbot_accuracy_boost_selection, g_config->aimbot_accuracy_boost_selection_items);
				ui::Checkbox("Anti-aim correction", &g_config->aimbot_anti_aim_correction);
				ui::Checkbox("Automatic fire", &g_config->aimbot_automatic_fire);
				ui::Checkbox("Automatic penetration", &g_config->aimbot_automatic_penetration);
				ui::Checkbox("Silent aim", &g_config->aimbot_silent_aim);
				ui::Checkbox("Remove recoil", &g_config->aimbot_remove_recoil);
				ui::Checkbox("Delay shot", &g_config->aimbot_delay_shot);
				ui::Checkbox("Quick peek assist", &g_config->aimbot_enabled); ui::KeyBind("###Quick peek assist", &g_config->aimbot_key, &g_config->aimbot_key_mode);
				ui::Label("Duck peek assist"); ui::KeyBind("###Duck peek assist", &g_config->aimbot_force_body_aim_key, &g_config->aimbot_force_body_aim_key_mode);
				ui::Checkbox("Reduce aim step", &g_config->aimbot_enabled);
				ui::SliderInt("Maximum FOV", &g_config->aimbot_min_damage, 0, 180, "%d°");
				ui::Checkbox("Log misses due to spread", &g_config->aimbot_enabled);
				ui::SingleSelect("Low FPS mitigations", &g_config->aimbot_multipoint_selection, g_config->aim_multipoint_selection_items);
			}
			ui::EndChild();

			ui::BeginChild("Aimbot", { Vec2(0, 0), Vec2(3, 10) });
			{
				ui::Checkbox("Enabled", &g_config->aimbot_enabled); ui::KeyBind("###Enable", &g_config->aimbot_key, &g_config->aimbot_key_mode);
				ui::SingleSelect("Target selection", &g_config->aimbot_target_selection, g_config->aim_target_selection_items);
				ui::SingleSelect("Target hitbox", &g_config->aimbot_target_hitbox_selection, g_config->aim_target_hitbox_selection_items);
				ui::SingleSelect("Multi-point", &g_config->aimbot_multipoint_selection, g_config->aim_multipoint_selection_items); ui::KeyBind("###Multi-point", &g_config->aimbot_multipoint, &g_config->aimbot_multipoint_key);
				ui::SliderInt("Minimum hit chance", &g_config->aimbot_hit_chance, 0, 100, g_config->aimbot_hit_chance < 1 ? "Off" : "%d%%");
				ui::SliderInt("Minimum damage", &g_config->aimbot_min_damage, 0, 126, g_config->aimbot_min_damage == 0 ? "Auto" : (g_config->aimbot_min_damage > 100 ? "HP+%d" : "%d"), (g_config->aimbot_min_damage > 100 ? 100 : 0));
				ui::Checkbox("Minimum damage override", &g_config->aimbot_min_damage_override); ui::KeyBind("###Minimum damage override", &g_config->aimbot_min_damage_override_key, &g_config->aimbot_min_damage_override_key_mode);
				ui::Checkbox("Prefer safe point", &g_config->aimbot_prefer_safe_point);
				ui::Label("Force safe point"); ui::KeyBind("###Force safe point", &g_config->aimbot_force_safe_point_key, &g_config->aimbot_force_safe_point_key_mode);
				ui::SingleSelect("Avoid unsafe hitboxes", &g_config->aimbot_target_hitbox_selection, g_config->aim_target_hitbox_selection_items);
				ui::Label("Force body aim"); ui::KeyBind("###Force body aim", &g_config->aimbot_force_body_aim_key, &g_config->aimbot_force_body_aim_key_mode);
				ui::Checkbox("Force body aim on peek", &g_config->aimbot_force_body_aim_on_peek);
				ui::Checkbox("Quick stop", &g_config->aimbot_quick_stop); ui::KeyBind("###Quick stop", &g_config->aimbot_quick_stop_key, &g_config->aimbot_quick_stop_key_mode);
				ui::Checkbox("Double tap", &g_config->aimbot_double_tap, true); ui::KeyBind("###Double tap", &g_config->aimbot_double_tap_key, &g_config->aimbot_double_tap_key_mode);
				ui::Checkbox("Automatic scope", &g_config->aimbot_automatic_scope);
			}
			ui::EndChild();

			break;
		}
	
		//
		// AA
		//
		case 1:
		{
			ui::BeginChild("Anti-aimbot angles"); 
			{
			}
			ui::EndChild();
		
			ui::BeginChild("Fake lag", {Vec2(6,0), Vec2(3, 5)}); {
			}
			ui::EndChild();

			ui::BeginChild("Other#AA", { Vec2(6,7), Vec2(3, 3) });
			{
			}
			ui::EndChild();

			break;
		}
		
		//
		// VFX
		//
		case 2:
		{
			ui::BeginChild("Player ESP", { Vec2(0,0), Vec2(3, 6) }); 
			{
			};
			ui::EndChild();
			ui::BeginChild("Colored models", { Vec2(0, 8), Vec2(3, 2) });
			{
			}
			ui::EndChild();
			ui::BeginChild("Other ESP", { Vec2(6, 0), Vec2(3, 3) });
			{
			}
			ui::EndChild();
			ui::BeginChild("Effects", { Vec2(6, 5), Vec2(3, 5) });
			{
			}
			ui::EndChild();
			
			break;
		}
	
		//
		// MISCELLANEOUS
		//
		case 3:
		{
			ui::BeginChild("Miscellaneous", { Vec2(0,0), Vec2(3, 10) });
			{
			}
			ui::EndChild();
			ui::BeginChild("Movement", { Vec2(6, 0), Vec2(3, 4) });
			{
			}
			ui::EndChild();
			ui::BeginChild("Settings", { Vec2(6, 6), Vec2(3, 4) });
			{
				ui::Label("Menu key"); ui::KeyBind("##Menu key", &g_config->menu_key, NULL);
				ui::Label("Menu color"); ui::ColorPicker("##Menu color", g_config->menu_color);
				ui::SingleSelect("DPI scale", &g_config->menu_dpi_scale, g_config->menu_dpi_scale_items);
				ui::Checkbox("Anti-untrusted", &g_config->menu_anti_untrusted);
				ui::Checkbox("Hide from OBS", &g_config->menu_hide_from_obs);
				ui::Checkbox("Low FPS warning", &g_config->menu_low_fps_warning);
				ui::Checkbox("Lock menu layout", &g_config->menu_lock_layout);
				ui::Button("Reset menu layout");
				ui::Button("Unload");
			}
			ui::EndChild();

			break;
		}
	
		//
		// SKINS & MODELS
		//
		case 4:
		{
			ui::BeginChild("Model options", { Vec2(0,0), Vec2(3, 10) });
			{
			}
			ui::EndChild();
			ui::BeginChild("Weapon skin", { Vec2(6, 0), Vec2(3, 10) });
			{
			}
			ui::EndChild();

			break;
		}

		case 5:
		{
			ui::BeginChild("Players", { Vec2(0,0), Vec2(3, 10) });
			{
				if (ui::BeginListbox("##Players", Vec2(90, 9))) {
					//Add players
					ui::EndListbox();
				}
				ui::Button("Reset all");
			}
			ui::EndChild();
			ui::BeginChild("Adjustments", { Vec2(6, 0), Vec2(3, 10) });
			{
				ui::Checkbox("Add to whitelist", &g_config->menu_lock_layout);
				ui::Checkbox("Allow shared ESP updates", &g_config->menu_lock_layout);
				ui::Checkbox("Disable visuals", &g_config->menu_lock_layout);
				ui::Checkbox("High priority", &g_config->menu_lock_layout);
				ui::Checkbox("Force pitch", &g_config->menu_lock_layout);
				ui::Checkbox("Force body yaw", &g_config->menu_lock_layout);
				ui::Checkbox("Correction active", &g_config->menu_lock_layout);
				ui::SingleSelect("Override prefer body aim", &g_config->menu_dpi_scale, g_config->menu_dpi_scale_items);
				ui::SingleSelect("Override safe point", &g_config->menu_dpi_scale, g_config->menu_dpi_scale_items);
				ui::Button("Apply to all");
			}
			ui::EndChild();

			break;
		}

	
		//
		// CFG & LUA
		//
		case 6:
		{
			ui::BeginChild("Presets", { Vec2(0,0), Vec2(3, 10) });
			{
				static std::vector<std::string> cfg_list = g_config->get_config_files();

				if (ui::BeginListbox("##CFGLIST"))
				{
					for (int i = 0; i < cfg_list.size(); i++)
					{
						if (ui::Selectable(cfg_list.at(i).c_str(), cfg_list.at(i) == g_config->selected_cfg))
							g_config->selected_cfg = cfg_list.at(i);
					}

					ui::EndListbox();
				}

				static char buf[64];
				ui::InputText("##CFGINPUT", buf);

				if (ui::Button("Refresh"))
					cfg_list = g_config->get_config_files();

				if (ui::Button("Create"))
				{
					if (std::string(buf) != "" && std::string(buf) != " " && !g_config->is_exist(buf))
					{
						g_config->save(buf, true);
						cfg_list = g_config->get_config_files();
					}
				}

				if (ui::Button("Save"))
					g_config->save(g_config->selected_cfg, false);

				if (ui::Button("Load"))
					g_config->load(g_config->selected_cfg);
			}
			ui::EndChild();
			ui::BeginChild("Lua", { Vec2(6, 0), Vec2(3, 10) });
			{
				static std::vector<std::string> lua_list = g_lua->scripts;
				static int selected_lua = -1;

				if (ui::BeginListbox("##LUALIST"))
				{
					for (int i = 0; i < lua_list.size(); i++)
					{
						std::string name = lua_list.at(i);
						if (ui::Selectable(name.c_str(), i == selected_lua || g_lua->loaded.at(i)))
							selected_lua = i;
					}

					ui::EndListbox();
				}

				if (ui::Button("Refresh"))
				{
					g_lua->refresh_scripts();
					lua_list = g_lua->scripts;
				}

				if (selected_lua > -1 && selected_lua < g_lua->scripts.size())
				{
					if (ui::Button("Load"))
					{
						g_lua->load_script(selected_lua);
						g_lua->refresh_scripts();
					}

					if (ui::Button("Unload"))
					{
						g_lua->unload_script(selected_lua);
						g_lua->refresh_scripts();
					}
				}
			}
			ui::EndChild();

			break;
		}
	
		case 7:
		{
			ui::BeginChild("A", { Vec2(0,0), Vec2(3, 10) });
			{
				for (int i = 0; i < g_lua->scripts.size(); i++)
				{
					auto& items = g_lua->items.at(i);

					for (auto& item : items)
					{
						std::string item_name;

						auto first_point = false;
						auto item_str = false;

						for (auto& c : item.first)
						{
							if (c == '.')
							{
								if (first_point)
								{
									item_str = true;
									continue;
								}
								else
									first_point = true;
							}

							if (item_str)
								item_name.push_back(c);
						}

						switch (item.second.type)
						{
						case LABEL:
							ui::Label(item.first.c_str());
							break;
						case CHECK_BOX:
							ui::Checkbox(item_name.c_str(), &item.second.check_box_value);
							break;
						case COMBO_BOX:
							ui::SingleSelect(item_name.c_str(), &item.second.combo_box_value, item.second.combo_box_labels);
							break;
						case SLIDER_INT:
							ui::SliderInt(item_name.c_str(), &item.second.slider_int_value, item.second.slider_int_min, item.second.slider_int_max);
							break;
						case SLIDER_FLOAT:
							ui::SliderFloat(item_name.c_str(), &item.second.slider_float_value, item.second.slider_float_min, item.second.slider_float_max, "%f", 0.1f);
							break;
						case COLOR_PICKER:
							ui::ColorPicker(item.first.c_str(), (int*)&item.second.color_picker_value);
							break;
						}
					}
				}

			}
			ui::EndChild();
			ui::BeginChild("B", { Vec2(6, 0), Vec2(3, 10) });
			ui::EndChild();
		}
	}

	ui::End();
}

bool CMenu::IsMenuOpened() 
{
	return this->m_bIsOpened;
}

void CMenu::SetMenuOpened(bool v) 
{
	this->m_bIsOpened = v;
}

D3DCOLOR CMenu::GetMenuColor() {
	GuiContext* g = Globals::Gui_Ctx;
	return D3DCOLOR_RGBA(g_config->menu_color[0], g_config->menu_color[1], g_config->menu_color[2], min(255, g->MenuAlpha));
}