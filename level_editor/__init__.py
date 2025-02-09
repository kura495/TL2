import bpy

# ブレンダーに登録するアドオン情報
bl_info = {
    "name": "レベルエディタ",
    "author": "Kuramoto Atsushi",
    "version": (1,0),
    "blender": (3,3,1),
    "location": "",
    "description": "レベルエディタ",
    "warning": "",
    "wiki_url": "",
    "tracker_url": "",
    "category": "Object"
}

#モジュールのインポート
from .stretch_vertex import MYADDON_OT_stretch_vertex
from .create_ico_sphere import MYADDON_OT_create_ico_sphere
from .export_scene import MYADDON_OT_export_scene
from .add_filename import MYADDON_OT_add_filename
from .add_filename import OBJECT_PT_file_name
from .add_collider import MYADDON_OT_add_collider
from .collider import OBJECT_PT_collider
from .draw_collider import DrawCollider
from .disabled import MYADDON_OT_disabled
from .disabled import OBJECT_PT_disabled
from .spawn import MYADDON_OT_spawn_import_symbol
from .spawn import MYADDON_OT_spawn_create_symbol
from .spawn import MYADDON_OT_player_spawn_Import_symbol
from .spawn import MYADDON_OT_enemy_spawn_Import_symbol

# トップバーの拡張メニュー
class TOPBAR_MT_my_menu(bpy.types.Menu):

    #Blenderがクラスを識別する為の固有の文字列
    bl_idname = "TOPBAR_MT_my_menu"
    #メニューのラベルとして表示される文字列
    bl_label = "MyMenu"
    #著者表示用の文字列
    bl_description = "拡張メニュー by " + bl_info["author"]

    #サブメニューの描画
    def draw(self, context):
        #トップバーの「エディターメニュー」に項目(オペレータ)を追加
        self.layout.operator("wm.url_open_preset",text = "Manual", icon = 'HELP')
        self.layout.operator(MYADDON_OT_stretch_vertex.bl_idname, text = MYADDON_OT_stretch_vertex.bl_label)
        self.layout.operator(MYADDON_OT_create_ico_sphere.bl_idname, text = MYADDON_OT_create_ico_sphere.bl_label)
        self.layout.operator(MYADDON_OT_export_scene.bl_idname,text = MYADDON_OT_export_scene.bl_label)
        self.layout.operator(MYADDON_OT_player_spawn_Import_symbol.bl_idname,text = MYADDON_OT_player_spawn_Import_symbol.bl_label)
        self.layout.operator(MYADDON_OT_enemy_spawn_Import_symbol.bl_idname,text = MYADDON_OT_enemy_spawn_Import_symbol.bl_label)

    # 既存のメニューにサブメニューを追加
    def submenu(self, context):
        #ID指定でサブメニューを追加
        self.layout.menu(TOPBAR_MT_my_menu.bl_idname)

# Blenderに登録するクラスリスト
classes = (
    MYADDON_OT_stretch_vertex,
    MYADDON_OT_create_ico_sphere,
    MYADDON_OT_export_scene,
    TOPBAR_MT_my_menu,
    MYADDON_OT_add_filename,
    OBJECT_PT_file_name,
    MYADDON_OT_add_collider,
    OBJECT_PT_collider,
    MYADDON_OT_disabled,
    OBJECT_PT_disabled,
    MYADDON_OT_spawn_create_symbol,
    MYADDON_OT_spawn_import_symbol,
    MYADDON_OT_player_spawn_Import_symbol,
    MYADDON_OT_enemy_spawn_Import_symbol
)

# アドオン有効化時コールバック
def register():
    # Blenderに登録するクラス
    for cls in classes:
        bpy.utils.register_class(cls)

    #メニューに項目を追加
    bpy.types.TOPBAR_MT_editor_menus.append(TOPBAR_MT_my_menu.submenu)
    #3Dビューに描画関数を追加
    DrawCollider.handle = bpy.types.SpaceView3D.draw_handler_add(DrawCollider.draw_collider, (), "WINDOW", "POST_VIEW")
    print("レベルエディタが有効化されました。")

# アドオン無効化時コールバック
def unregister():
    #メニューに項目を削除
    bpy.types.TOPBAR_MT_editor_menus.remove(TOPBAR_MT_my_menu.submenu)
    #3Dビューから描画関数を削除
    bpy.types.SpaceView3D.draw_handler_remove(DrawCollider.handle, "WINDOW")    
    
    # Blenderに登録したクラスを削除
    for cls in classes:
        bpy.utils.unregister_class(cls)
    print("レベルエディタが無効化されました。")
    
#test
if __name__ == "__main__":
    register()

