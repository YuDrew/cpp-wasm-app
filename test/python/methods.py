import pandas as pd

# returns a sorted list of options from a multi-select Affinity field
def extract_all_options_from_multiselect_field(df: pd.DataFrame, multiselect_field: str, option_list: list(str) =[]) -> list(str):
    field_list = list(set(list(df[multiselect_field].unique())))
    for entry in field_list:
        # entry is a string of options separated by "; "
        option_list += [x.strip() for x in str(entry).split("; ")]
    # remove identical duplicates.
    option_list = list(set(option_list))
    return option_list

def enrich_investors(deals_df, organizations_df):
    investor_list = extract_all_options_from_multiselect_field(deals_df, 'Investors')
    ''' 
    at this point, there are several duplicates in the list with slightly different names
    generally this is not a big deal, since we're going to be merging this list into the
    organization list anyway, and we shouldn't get duplicates there unless our organization
    list has duplicates (which we shouldn't, and if we do, affinity will suggest fixing it)
    '''
    investor_df = pd.DataFrame(investor_list, columns=['Name'])

    # pull out the Sector Sub-Sector and Tech Trend(s) from each portco, and map to investors
    for investor in investor_df['Name']:
        sector_dict = {}
        subsector_dict = {}
        tech_dict = {}
        for _, row in deals_df.iterrows():
            if investor in row['Investors']:
                sector_dict[str(row['Sector'])] = sector_dict.get(str(row['Sector']), 0) + 1
                subsector_dict[str(row['Sub-Sector'])] = subsector_dict.get(str(row['Sub-Sector']), 0) + 1
                tech_dict[str(row['Tech Trend(s)'])] = tech_dict.get(str(row['Tech Trend(s)']), 0) + 1
        sector_dict.pop('nan',None)
        subsector_dict.pop('nan',None)
        tech_dict.pop('nan',None)
        investor_df.loc[investor_df['Name'] == investor, 'Sector'] = '; '.join(sorted(sector_dict, key=sector_dict.get, reverse=True))
        investor_df.loc[investor_df['Name'] == investor, 'Sub-Sector'] = '; '.join(sorted(subsector_dict, key=subsector_dict.get, reverse=True))
        investor_df.loc[investor_df['Name'] == investor, 'Tech Trend(s)'] = '; '.join(sorted(tech_dict, key=tech_dict.get, reverse=True))
        '''NOTE: this creates duplicates of each field in the investor list, but this doesn't matter because Affinity squashes duplicates'''

    # merge organization list websites to investor list
    # first create a lowercase name for both the organization and investor list
    organizations_df['lower'] = organizations_df['Name'].str.lower()
    investor_df['lower'] = investor_df['Name'].str.lower()
    # merge the two lists on the lowercase name
    enriched_investors_df = pd.merge(organizations_df[['Name', 'Website', 'lower']], investor_df[['lower', 'Sector','Sub-Sector','Tech Trend(s)']], on='lower')
    # drop the lowercase column
    enriched_investors_df = enriched_investors_df.drop(columns='lower')
    #enriched_investors_df.to_csv('explore/enriched_investors.csv')
    return enriched_investors_df

def infer_sectors(deals_df):
    # create the initial list of Industries from the Affinity integration for "Industry"
    industry_list = extract_all_options_from_multiselect_field(deals_df, 'Industry')
    industry_df = pd.DataFrame(industry_list, columns=['Name'])

    # match industries from Affinity to proprietary list
    industry_df['lower'] = industry_df['Name'].str.lower().fillna('')
    target_sector_list = ['Energy', 'Transportation + Logistics', 'Food + AgTech', 'Carbon', 'Cross-Sector']
    for sector in target_sector_list:
        for word in sector.lower().replace('+ ','').split():
            # if the industry contains the word, add sector to the industry list
            # this fails for "Built Environment" because "Environment" is in the list
            # so I'm literally just not including Built Environment for now
            # TODO: make this much more robust
            industry_df.loc[industry_df['lower'].str.contains(word), 'Sector'] = str(sector)
    industry_df = industry_df.drop(columns='lower')
    industry_df = industry_df.dropna()

    # If the deal has a industry, add the associated sector to the deal
    for index, row in deals_df.iterrows():
        if row['Industry'] != 'nan':
            for _, row2 in industry_df.iterrows():
                if row2['Name'] in str(row['Industry']) and row2['Sector'] != 'nan':
                    if str(row['Sector']) != 'nan':
                        deals_df.loc[index, 'Sector'] = str(row['Sector']) + '; ' + str(row2['Sector'])
                    else:
                        deals_df.loc[index, 'Sector'] = str(row2['Sector'])
    return deals_df