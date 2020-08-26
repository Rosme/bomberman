import sys
from os import listdir
from os.path import isfile, join
import xml.etree.ElementTree as ET
import xml.dom.minidom

def convert_map(directory_path):
    map_files = [f for f in listdir(directory_path) if isfile(join(directory_path, f))]
    for file in map_files:
        if file == 'bob.mp':
            continue
        with open(directory_path + '/' + file) as f:
            input_tree = ET.parse(f)
        input_root = input_tree.getroot()

        output_root = ET.Element('cereal')
        output_map = ET.Element('map')
        output_root.append(output_map)
        output_cereal_class = ET.Element('cereal_class_version')
        output_cereal_class.text = '0'
        output_map.append(output_cereal_class)
        
        output_value0 = ET.Element('value0')
        output_value0.text = '27'
        output_value1 = ET.Element('value1')
        output_value1.text = '21'

        output_map.append(output_value0)
        output_map.append(output_value1)

        for node in input_root:
            if node.tag == 'map':
                for subnode in node:
                    if subnode.tag == 'm_name':
                        output_name = ET.Element('value569')
                        output_name.text = subnode.text
                        output_map.append(output_name)
                    if subnode.tag == 'm_players':
                        value_player = 570
                        for player in subnode:
                            if player.tag == 'item':
                                player_pos = list(player)
                                output_player = ET.Element("value{}".format(value_player))
                                if value_player == 570:
                                    player_cereal_class_version = ET.Element('cereal_class_version')
                                    player_cereal_class_version.text = '0'
                                    output_player.append(player_cereal_class_version)
                                output_pos_x = ET.Element('value0')
                                output_pos_x.text = player_pos[0].text
                                output_player.append(output_pos_x)
                                output_pos_y = ET.Element('value1')
                                output_pos_y.text = player_pos[1].text
                                output_player.append(output_pos_y)
                                output_map.append(output_player)
                                value_player += 1
                    if subnode.tag == 'm_array':
                        for tag in subnode:
                            if tag.tag == 'data':
                                value_array = 2
                                for item in tag:
                                    item_values = list(item)

                                    output_item = ET.Element("value{}".format(value_array))
                                    if value_array == 2:
                                        item_cereal_class_version = ET.Element('cereal_class_version')
                                        item_cereal_class_version.text = '0'
                                        output_item.append(item_cereal_class_version)
                                    
                                    pos_x = ET.Element("value0")
                                    pos_x.text = item_values[0].text
                                    output_item.append(pos_x)
                                    
                                    pos_y = ET.Element("value1")
                                    pos_y.text = item_values[1].text
                                    output_item.append(pos_y)
                                    
                                    properties = ET.Element("value2")
                                    properties.text = item_values[2].text
                                    output_item.append(properties)
                                    
                                    tile_type = ET.Element("value3")
                                    tile_type.text = item_values[3].text
                                    output_item.append(tile_type)
                                    output_map.append(output_item)
                                    value_array += 1

        output_tree =  ET.ElementTree(output_root)
        with open (directory_path + '/' + file, 'wb') as f:
            output_tree.write(f, encoding='utf-8', xml_declaration=True)
        

        
        


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Requires path to map folder")
        exit(1)
    
    convert_map(sys.argv[1])

    