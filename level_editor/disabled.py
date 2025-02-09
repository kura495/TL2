import bpy

#オペレータ　無効オプションを追加する
class MYADDON_OT_disabled(bpy.types.Operator):
    bl_idname = "myaddon.myaddon_ot_disabled"
    bl_label = "無効オプション"
    bl_description = "無効オプションのON/OFFを切り替えます"
    bl_options = {'REGISTER', 'UNDO'}

    def execute(self,context):
        #["disabled"]カスタムプロパティを追加
        context.object["disabledFlag"] = True
        return {"FINISHED"}

#無効オプションパネル
class OBJECT_PT_disabled(bpy.types.Panel):
    bl_idname = "OBJECT_PT_disabled"
    bl_label = "disabled"
    bl_space_type = "PROPERTIES"
    bl_region_type = "WINDOW"
    bl_context = "object"

    #サブメニューの描画
    def draw(self,context):
        #パネルに項目を追加
        if "disabledFlag" in context.object:
            #既にプロパティがあれば、プロパティを表示
            self.layout.prop(context.object, '["disabledFlag"]', text=self.bl_label)
        else:
            #プロパティが無ければ、プロパティ追加ボタンを表示
            self.layout.operator(MYADDON_OT_disabled.bl_idname)